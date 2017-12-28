/*
 * Copyright 2017 <Gustavo Pantuza>
 *
 * ============================================================================
 *
 *       Filename:  stack_client.h
 *
 *    Description:  C++ header file for gRPC Stack service
 *
 *        Version:  0.1
 *        Created:  12/28/2017 18:01:52 PM
 *       Compiler:  g++
 *
 *         Author:  Gustavo Pantuza (gustavopantuza@gmail.com)
 *   Organization:  Computer science community
 *
 * ============================================================================
 */

#ifndef SERVICES_STACK_STACK_CLIENT_H_
#define SERVICES_STACK_STACK_CLIENT_H_

#include <iostream>
#include <string>
#include <sstream>

#include <grpc++/grpc++.h>

#include "./stack.grpc.pb.h"

#include "./config.h"


using std::cout;
using std::endl;
using std::cin;
using std::string;
using std::getline;
using std::ostringstream;

using grpc::Channel;
using grpc::ClientContext;
using grpc::Status;

using StackService::StackServer;
using DogType::Dog;
using StackService::Empty;
using StackService::StackSizeResponse;
using StackService::StackBoolResponse;


class StackClient {
 private:
    std::unique_ptr<StackServer::Stub> stub_;
 public:
    explicit StackClient(std::shared_ptr<Channel> channel)
    : stub_(StackServer::NewStub(channel))
    {}

    bool Push(Dog item) {
        ClientContext context;
        Empty reply;

        Status status = this->stub_->Push(&context, item, &reply);
        if (status.ok()) {
            return true;
        } else {
            std::cout << status.error_code() << ": " << status.error_message()
                << std::endl;
        }

        return false;
    }

    Dog* Pop() {
        ClientContext context;
        Empty none;
        Dog* item = new Dog();

        Status status = this->stub_->Pop(&context, none, item);

        if (status.ok()) {
            return item;
        } else {
            std::cout << status.error_code() << ": " << status.error_message()
                << std::endl;
        }
        return NULL;
    }

    StackSizeResponse* Size()
    {
        ClientContext context;
        Empty none;
        StackSizeResponse* size = new StackSizeResponse();
        Status status = this->stub_->Size(&context, none, size);

        if (status.ok()) {
            return size;
        } else {
            std::cout << status.error_code() << ": " << status.error_message()
                << std::endl;
            return NULL;
        }
    }

    StackBoolResponse* IsEmpty()
    {
        ClientContext context;
        Empty none;
        StackBoolResponse* response = new StackBoolResponse();

        Status status = this->stub_->IsEmpty(&context, none, response);
        if (status.ok()) {
            return response;
        } else {
            std::cout << status.error_code() << ": " << status.error_message()
                << std::endl;
            return NULL;
        }
    }

    StackBoolResponse* Clear()
    {
        ClientContext context;
        Empty none;
        StackBoolResponse* response = new StackBoolResponse();

        Status status = this->stub_->Clear(&context, none, response);
        if (status.ok()) {
            return response;
        } else {
            std::cout << status.error_code() << ": " << status.error_message()
                << std::endl;
            return NULL;
        }
    }
};
