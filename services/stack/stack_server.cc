#include <iostream>
#include <string>
#include <sstream>
#include <stack>

#include <grpc++/grpc++.h>

#include "./stack.grpc.pb.h"
#include "./spdlog/spdlog.h"

#include "./config.h"


using std::string;
using std::ostringstream;
using std::stack;
using std::cout;
using std::endl;
using std::shared_ptr;

using grpc::ServerContext;
using grpc::Status;
using grpc::StatusCode;
using grpc::ServerBuilder;
using grpc::Server;

using StackService::StackServer;
using DogType::Dog;
using StackService::Empty;
using StackService::StackSizeResponse;
using StackService::StackBoolResponse;


class StackServerImpl final : public StackServer::Service {
 private:
    stack<Dog> items;
    shared_ptr<spdlog::logger> console;

 public:
    StackServerImpl() :StackServer::Service()
    {
        this->console = spdlog::get("Stack");
        if (!this->console) {
            this->console = spdlog::stdout_color_mt("Stack");
        }
        this->console->info("Stack service");
    }

    Status Push(ServerContext* context, const Dog* item, Empty* reply)
    override {
        this->items.push(*item);
        this->console->info("Push({0}) - size[{1}]",
                            item->name(), this->items.size());
        return Status::OK;
    }

    Status Pop(ServerContext* context, const Empty* none, Dog* item) override
    {
        if(this->items.empty()) {
            Status status(StatusCode::OUT_OF_RANGE, "The stack is empty");
            return status;
        }
        item->set_name(this->items.top().name());
        this->items.pop();
        this->console->info("Pop({0}) - size[{1}]",
                            item->name(), this->items.size());
        return Status::OK;
    }

    Status Size(ServerContext* context, const Empty* none,
                StackSizeResponse* size) override
    {
        size->set_value(this->items.size());
        return Status::OK;
    }

    Status IsEmpty(ServerContext* context, const Empty* none,
                   StackBoolResponse* response) override
    {
        response->set_value(this->items.empty());
        return Status::OK;
    }
};


void RunServer(StackConfigLoader config) {

    ostringstream ostr;
    ostr << config.addr << ":" << config.port;
    string serverAddress(ostr.str());

    StackServerImpl service;
    ServerBuilder builder;

    builder.AddListeningPort(serverAddress, grpc::InsecureServerCredentials());
    builder.RegisterService(&service);

    std::unique_ptr<Server> server(builder.BuildAndStart());
    spdlog::get("Stack")->info("Listening on port {0}", serverAddress);

    server->Wait();
}


int main(int argc, char* argv[]) {

    string config_file = "/etc/vetulus/services/stack_server.conf";

    if (argc > 1) {
        config_file = argv[1];
    }

    StackConfigLoader config;
    config.load(config_file);

    RunServer(config);

    return EXIT_SUCCESS;
}
