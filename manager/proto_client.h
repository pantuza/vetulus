
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
using VetulusService::ProtoServer;


class ProtoClient {
 private:
    std::unique_ptr<ProtoServer::Stub> stub_;
 public:
    explicit ProtoClient(std::shared_ptr<Channel> channel)
    : stub_(ProtoServer::NewStub(channel))
    {}

    bool Load(const ProtoFile* file) {
        ClientContext context;
        Ack ack;

        Status status = stub_->Load(&context, *file, &ack);

        if (status.ok() && ack.done()) {
            cout << "Writes done" << endl;
            return true;
        } else {
            cerr << "Error on write" << endl;
            return false;
        }
    }

    string ReadFileAsString(const string path)
    {
        ifstream proto_file(path.c_str());
        stringstream buffer;
        buffer << proto_file.rdbuf();
        proto_file.close();
        return buffer.str();
    }
};

#endif // MANAGER_PROTO_CLIENT_H_
