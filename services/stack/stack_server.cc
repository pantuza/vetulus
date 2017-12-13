#include <iostream>
#include <string>
#include <sstream>
#include <stack>

#include <grpc++/grpc++.h>

#include "./stack.grpc.pb.h"

#include "./config.h"


using std::string;
using std::ostringstream;
using std::stack;
using std::cout;
using std::endl;

using grpc::ServerContext;
using grpc::Status;
using grpc::ServerBuilder;
using grpc::Server;

using StackService::StackServer;
using DogType::Dog;
using StackService::Empty;


class StackServerImpl final : public StackServer::Service {
 private:
    stack<Dog> items;

    Status Push(ServerContext* context, const Dog* item, Empty* reply)
    override {
        items.push(*item);
        cout << "push(" << item->name() << ") - size[" << items.size() << "]" << endl;
        return Status::OK;
    }

    Status Pop(ServerContext* context, const Empty* none,
               Dog* item) override {
        item->set_name(items.top().name());
        items.pop();
        cout << "pop(" << item->name() << ") - size[" << items.size() << "]" << endl;
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
    cout << "Listening on port " << serverAddress << endl;

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
