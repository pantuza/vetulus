
#ifndef MANAGER_PROTO_CLIENT_H_
#define MANAGER_PROTO_CLIENT_H_

#include <iostream>
#include <string>
#include <sstream>

#include <grpc++/grpc++.h>

#include "./stack.grpc.pb.h"

#include "./config.h"

using std::cout;
using std::cerr;
using std::endl;
using std::unique_ptr;

using grpc::Channel;
using grpc::ClientContext;
using grpc::ClientWritter;
using grpc::Status;

using VetulusService::ProtoFile;
using VetulusService::Ack;
using VetulusService::ProtoServer;


class ProtoClient {
 private:
    std::unique_ptr<ProtoServer::Stub> stub_;
 public:
    explicit ProtoClient(std::shared_ptr<Channel> channel)
    : stub_(ProtoServer::NewStub(channel))
    {}

    bool Load(ProtoFile file) {
        ClientContext context;
        Ack ack;

        std::unique_ptr<ClientWritter<ProtoFile>> writer(
                stub_->Load(&context, &ack));

        writer->WritesDone();
        Status status = writer->Finish();
        if (status.ok() && ack.done()) {
            cout << "Writes done" << endl;
            return true;
        } else {
            cerr << "Error on write" << endl;
            return false;
        }
    }
};

#endif // MANAGER_PROTO_CLIENT_H_
