#include <iostream>
#include <string>
#include <stack>

#include <grpc++/grpc++.h>

#include "./stack.grpc.pb.h"


using std::string;
using std::stack;
using std::cout;
using std::endl;

using grpc::ServerContext;
using grpc::Status;
using grpc::ServerBuilder;
using grpc::Server;

using server::StackServer;
using server::Item;
using server::NoneParam;
using server::StackResponse;


class StackServerImpl final : public StackServer::Service {
 private:
    stack<Item> items;

    Status Push(ServerContext* context, const Item* item, StackResponse* reply)
    override {
        items.push(*item);
        cout << "push(" << item->name() << ") - size[" << items.size() << "]" << endl;
        reply->set_status(true);
        return Status::OK;
    }

    Status Pop(ServerContext* context, const NoneParam* none,
               Item* item) override {
        item->set_name(items.top().name());
        items.pop();
        cout << "pop(" << item->name() << ") - size[" << items.size() << "]" << endl;
        return Status::OK;
    }
};

void RunServer() {
    std::string serverAddress("0.0.0.0:50051");
    StackServerImpl service;
    ServerBuilder builder;

    builder.AddListeningPort(serverAddress, grpc::InsecureServerCredentials());
    builder.RegisterService(&service);

    std::unique_ptr<Server> server(builder.BuildAndStart());
    cout << "Listening on port " << serverAddress << endl;

    server->Wait();
}

int main(int argc, char* argv[]) {
    RunServer();

    return EXIT_SUCCESS;
}
