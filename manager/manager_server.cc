/*
 * Copyright 2018 <Gustavo Pantuza>
 *
 * ============================================================================
 *
 *       Filename:  manager_server.cpp
 *
 *    Description:  Implementation of the manager server. It controls and
 *                  forks new services.
 *
 *        Version:  1.0
 *        Created:  12/03/2018 10:43:22 AM
 *       Compiler:  g++
 *
 *         Author:  Gustavo Pantuza (gustavopantuza@gmail.com)
 *   Organization:  Computer science community
 *
 * ============================================================================
 */



#include <unistd.h>

#include <iostream>

#include <string>
#include <sstream>
#include <fstream>

#include <grpc++/grpc++.h>

#include "./service.grpc.pb.h"
#include "./spdlog/spdlog.h"

#include "./config.h"
#include "./proto_loader.h"
#include "./process.h"


// #include "./stack/stack_client.h"


using std::string;
using std::ifstream;
using std::stringstream;
using std::ostringstream;
using std::shared_ptr;

using grpc::ServerContext;
using grpc::Status;
using grpc::StatusCode;
using grpc::ServerBuilder;
using grpc::Server;

using VetulusService::ProtoFile;
using VetulusService::Ack;
using VetulusService::Manager;
using VetulusService::MetaData;

using VetulusService::ADTService;
using VetulusService::ListOptions;
using VetulusService::ListResponse;

using VetulusService::ADTImpl;
using VetulusService::ListADTsOptions;
using VetulusService::ListADTsResponse;

using manager::VetulusProtoBuilder;

using processes::VetulusProcess_t;
using processes::VetulusProcess;


class ManagerServer final : public Manager::Service {
 private:
    shared_ptr<spdlog::logger> console;
    VetulusProcess processes;

 public:
    ManagerServer()
    : Manager::Service()
    {
        this->console = spdlog::get("Manager");
        if (!this->console) {
            this->console = spdlog::stdout_color_mt("Manager");
        }
        this->console->info("Manager Server");
    }

    Status Add(ServerContext* context, const ProtoFile* proto,
                Ack* ack) override
    {
        string file_name = proto->meta().name() + ".proto";
        this->console->info("Add({0})", file_name);

        /* If file already exists we do not upload it */
        ifstream infile(file_name.c_str());
        if (infile.good()) {
            ack->set_done(false);
            this->console->error("Could not load file {0}. "
                                 "File already exists", file_name);
            return Status::OK;
        } else {
            ofstream proto_file(file_name.c_str());
            proto_file << proto->data();
            proto_file.close();

            VetulusProtoBuilder builder;
            if (builder.Import(file_name)) {
                if (builder.CppGenerate()) {
                    ack->set_done(true);
                    return Status::OK;
                }
            }
            ack->set_done(false);
            return Status::OK;
        }
    }

    Status Remove(ServerContext* context, const MetaData* meta,
                  Ack* ack) override
    {
        string proto_name = meta->name();
        string proto = proto_name + ".proto";
        string header = proto_name + ".pb.h";
        string source = proto_name + ".pb.cc";

        bool done = true;
        if (remove(proto.c_str()) != 0) {
            done = false;
            this->console->error("Remove({0}): fail", proto);
        }
        if (remove(header.c_str()) != 0) {
            done = false;
            this->console->error("Remove({0}): fail", header);
        }
        if (remove(source.c_str()) != 0) {
            done = false;
            this->console->error("Remove({0}): fail", source);
        }
        ack->set_done(done);
        return Status::OK;
    }

    Status Start(ServerContext* context, const ADTService* adt,
                    Ack* ack) override
    {
      pid_t pid = fork();

      if(pid == 0) {  // Forked child process execution block

        this->runForkedServer(adt);

      } else if(pid > 0) {  // Parent process execution block

        VetulusProcess_t proc_data;

        proc_data.process_pid = pid;
        proc_data.parent_pid = getpid();
        proc_data.name = adt->name();
        proc_data.port = adt->port();
        proc_data.adt = *adt;

        processes.Add(proc_data);

        this->console->info("Server forked: '{0}'", adt->name());

        ack->set_done(true);
        return Status::OK;

      } else {  // Fork error

        this->console->error("Server fork failed: '{0}'", adt->name());
        return Status::CANCELLED;
      }

      ack->set_done(true);
      return Status::OK;
    }

    Status Stop(ServerContext* context, const ADTService* adt,
                    Ack* ack) override
    {
        if (processes.Remove(adt->name())) {

          this->console->info("Server killed: '{0}'", adt->name());
          ack->set_done(true);
          return Status::OK;
        }

        return Status::CANCELLED;
    }

    Status ListServices(ServerContext* context, const ListOptions* opts,
                        ListResponse* response) override
    {

      for (auto& i : processes.All()) {
        ADTService* service = response->add_services();
        service = &i.adt;
      }

      return Status::OK;
    }

    Status ListADTs(ServerContext* context, const ListADTsOptions* opts,
                    ListADTsResponse* response) override
    {
      return Status::OK;
    }

    bool runForkedServer(const ADTService* adt)
    {

      ostringstream ostr;
      ostr << adt->address() << ":" << adt->port();
      string serverAddress(ostr.str());

      ManagerServer service;
      ServerBuilder builder;

      builder.AddListeningPort(serverAddress, grpc::InsecureServerCredentials());
      builder.RegisterService(&service);

      std::unique_ptr<Server> server(builder.BuildAndStart());

      console = spdlog::get(adt->name());
      if (!console) {
        console = spdlog::stdout_color_mt(adt->name());
      }

      console->info(
        "{0} service listening on port {1}", adt->name(), serverAddress
      );
      server->Wait();
    }
};


int
main(int argc, char* argv[])
{
    string config_file = "/etc/vetulus/services/manager_server.conf";

    if (argc > 1) {
        config_file = argv[1];
    }

    ProtoConfigLoader config;
    config.load(config_file);

    ostringstream ostr;
    ostr << config.addr << ":" << config.port;
    string serverAddress(ostr.str());

    ManagerServer service;
    ServerBuilder builder;

    builder.AddListeningPort(serverAddress, grpc::InsecureServerCredentials());
    builder.RegisterService(&service);

    std::unique_ptr<Server> server(builder.BuildAndStart());
    spdlog::get("Manager")->info("Listening on port {0}", serverAddress);

    server->Wait();

    return EXIT_SUCCESS;
}
