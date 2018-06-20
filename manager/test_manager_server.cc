/*
 * Copyright 2017 <Gustavo Pantuza>
 *
 * ============================================================================
 *
 *       Filename:  test_manager_server.cc
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
using VetulusService::ADTService;


/* Tests loading a protobuffer file */
TEST(ManagerServiceTest, TestLoadProtobuffer)
{
    ProtoClient client(grpc::CreateChannel(
                   "vetulus:42501", grpc::InsecureChannelCredentials()));

    string bytes = client.ReadFileAsString("/vetulus/protos/dog.proto");
    ProtoFile file;
    file.set_data(bytes);
    file.mutable_meta()->set_name("Dog0");

    ASSERT_TRUE(client.Load(&file));
    ASSERT_TRUE(client.Unload(file.meta().name()));
}


/* Tests if there is a error when we can not import a file */
TEST(ManagerServiceTest, TestCantLoadProtobuffer)
{
    ProtoClient client(grpc::CreateChannel(
                   "vetulus:42501", grpc::InsecureChannelCredentials()));
    ProtoFile file;
    file.set_data("invalid data");
    file.mutable_meta()->set_name("Invalid");

    ASSERT_FALSE(client.Load(&file));
}


/* Tests if there is a error when we can not import a file */
TEST(ManagerServiceTest, TestCheckIfProtoFileWereGenerated)
{
    ProtoClient client(grpc::CreateChannel(
                   "vetulus:42501", grpc::InsecureChannelCredentials()));

    string bytes = client.ReadFileAsString("/vetulus/protos/dog.proto");
    ProtoFile file;
    file.set_data(bytes);
    file.mutable_meta()->set_name("Dog1");

    client.Load(&file);
    ifstream protofile("Dog1.proto");

    ASSERT_TRUE(protofile.good());
    ASSERT_TRUE(client.Unload(file.meta().name()));
}


/* Tests if there is a error when we can not import a file */
TEST(ManagerServiceTest, TestCheckIfCppFilesWereGenerated)
{
    ProtoClient client(grpc::CreateChannel(
                   "vetulus:42501", grpc::InsecureChannelCredentials()));

    string bytes = client.ReadFileAsString("/vetulus/protos/dog.proto");
    ProtoFile file;
    file.set_data(bytes);
    file.mutable_meta()->set_name("Dog2");
    client.Load(&file);

    ifstream headerfile("Dog2.pb.h");
    ifstream sourcefile("Dog2.pb.cc");

    ASSERT_TRUE(headerfile.good());
    ASSERT_TRUE(sourcefile.good());
    ASSERT_TRUE(client.Unload(file.meta().name()));
}


/* Tests Unloading an imported protofile */
TEST(ManagerServiceTest, TestRemoveAProtofile)
{
    ProtoClient client(grpc::CreateChannel(
                   "vetulus:42501", grpc::InsecureChannelCredentials()));

    string bytes = client.ReadFileAsString("/vetulus/protos/dog.proto");
    ProtoFile file;
    file.set_data(bytes);
    file.mutable_meta()->set_name("Dog3");
    client.Load(&file);

    ASSERT_TRUE(client.Unload("Dog3"));
}


/* Tests if is not possible to upload same file twice */
TEST(ManagerServiceTest, TestUploadProtoTwice)
{
    ProtoClient client(grpc::CreateChannel(
                   "vetulus:42501", grpc::InsecureChannelCredentials()));

    string bytes = client.ReadFileAsString("/vetulus/protos/dog.proto");
    ProtoFile file;
    file.set_data(bytes);
    file.mutable_meta()->set_name("Dog0");
    client.Load(&file);
    ASSERT_FALSE(client.Load(&file));
    ASSERT_TRUE(client.Unload(file.meta().name()));
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
