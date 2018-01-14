/*
 * Copyright 2017 <Gustavo Pantuza>
 *
 * ============================================================================
 *
 *       Filename:  test_proto_server.cc
 *
 *    Description:  Test program for the gRPC Proto service
 *
 *        Version:  0.1
 *        Created:  01/09/2018 20:16:52 PM
 *       Compiler:  g++
 *
 *         Author:  Gustavo Pantuza (gustavopantuza@gmail.com)
 *   Organization:  Computer science community
 *
 * ============================================================================
 */

#ifndef SERVICE_PROTO_TEST_H_
#define SERVICE_PROTO_TEST_H_

#include <iostream>
#include <string>
#include <sstream>

#include <gtest/gtest.h>

#include "./config.h"
#include "./proto_client.h"


using VetulusService::ProtoFile;
using VetulusService::MetaData;


/* Tests loading a protobuffer file */
TEST(ProtoServiceTest, TestLoadProtobuffer)
{
    ProtoClient client(grpc::CreateChannel(
                   "172.17.0.2:42501", grpc::InsecureChannelCredentials()));

    string bytes = client.ReadFileAsString("/vetulus/protos/dog.proto");
    ProtoFile file;
    file.set_data(bytes);
    file.mutable_meta()->set_name("Dog");

    ASSERT_TRUE(client.Load(&file));
}


/* Tests if there is a error when we can not import a file */
TEST(ProtoServiceTest, TestCantLoadProtobuffer)
{
    ProtoClient client(grpc::CreateChannel(
                   "172.17.0.2:42501", grpc::InsecureChannelCredentials()));
    ProtoFile file;
    file.set_data("invalid data");
    file.mutable_meta()->set_name("Invalid");

    ASSERT_FALSE(client.Load(&file));
}


int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);

    string config_file = "/etc/vetulus/services/proto_client.conf";

    if (argc > 1) {
        config_file = argv[1];
    }

    ProtoConfigLoader config;
    config.load(config_file);

    ostringstream config_str;

    return RUN_ALL_TESTS();
}


#endif  // SERVICE_STACK_TEST_H_
