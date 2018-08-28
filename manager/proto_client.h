
#ifndef MANAGER_PROTO_CLIENT_H_
#define MANAGER_PROTO_CLIENT_H_

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#include <grpc++/grpc++.h>

#include "./service.grpc.pb.h"

#include "./config.h"

using std::cout;
using std::cerr;
using std::endl;
using std::unique_ptr;
using std::string;
using std::ifstream;
using std::stringstream;

using grpc::Channel;
using grpc::ClientContext;
using grpc::Status;

using VetulusService::ProtoFile;
using VetulusService::Ack;
using VetulusService::Manager;
using VetulusService::MetaData;
using VetulusService::ADTService;
using VetulusService::ListOptions;
using VetulusService::ListResponse;


class ProtoClient {
 private:
    std::unique_ptr<Manager::Stub> stub_;
 public:
    explicit ProtoClient(std::shared_ptr<Channel> channel)
    : stub_(Manager::NewStub(channel))
    {}

    bool Load(const ProtoFile* file)
    {
        ClientContext context;
        Ack ack;

        Status status = stub_->Load(&context, *file, &ack);

        if (status.ok() && ack.done()) {
            return true;
        } else {
            return false;
        }
    }

    bool Unload(const string protofile)
    {
        ClientContext context;
        Ack ack;
        MetaData meta;
        meta.set_name(protofile);

        Status status = stub_->Unload(&context, meta, &ack);

        if (status.ok() && ack.done()) {
            return true;
        }
        return false;
    }

    string ReadFileAsString(const string path)
    {
        ifstream proto_file(path.c_str());
        stringstream buffer;
        buffer << proto_file.rdbuf();
        proto_file.close();
        return buffer.str();
    }

    bool Register(const ADTService* adt)
    {
      ClientContext context;
      Ack ack;
      Status status = stub_->Register(&context, *adt, &ack);

      if (status.ok() && ack.done()) {
          return true;
      }
      return false;
    }

    bool Unregister(const ADTService* adt)
    {
      ClientContext context;
      Ack ack;
      Status status = stub_->Unregister(&context, *adt, &ack);

      if (status.ok() && ack.done()) {
          return true;
      }
      return false;
    }

    ListResponse ListServices (const ListOptions* opts)
    {
      ClientContext context;
      ListResponse response;
      Status status = stub_->ListServices(&context, *opts, &response);

      return response;
    }
};

#endif // MANAGER_PROTO_CLIENT_H_
