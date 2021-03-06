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
using VetulusService::ListOptions;
using VetulusService::ListResponse;



/* Tests loading a protobuffer file */
TEST(ManagerServiceTest, TestAddProtobuffer)
{
    ProtoClient client(grpc::CreateChannel(
                   "vetulus:4242", grpc::InsecureChannelCredentials()));

    string bytes = client.ReadFileAsString("/vetulus/protos/dog.proto");
    ProtoFile file;
    file.set_data(bytes);
    file.mutable_meta()->set_name("Dog0");

    ASSERT_TRUE(client.Add(&file));
    ASSERT_TRUE(client.Remove(file.meta().name()));
}


/* Tests if there is a error when we can not import a file */
TEST(ManagerServiceTest, TestCantAddProtobuffer)
{
    ProtoClient client(grpc::CreateChannel(
                   "vetulus:4242", grpc::InsecureChannelCredentials()));
    ProtoFile file;
    file.set_data("invalid data");
    file.mutable_meta()->set_name("Invalid");

    ASSERT_FALSE(client.Add(&file));
}


/* Tests if there is a error when we can not import a file */
TEST(ManagerServiceTest, TestCheckIfProtoFileWereGenerated)
{
    ProtoClient client(grpc::CreateChannel(
                   "vetulus:4242", grpc::InsecureChannelCredentials()));

    string bytes = client.ReadFileAsString("/vetulus/protos/dog.proto");
    ProtoFile file;
    file.set_data(bytes);
    file.mutable_meta()->set_name("Dog1");

    client.Add(&file);
    ifstream protofile("Dog1.proto");

    ASSERT_TRUE(protofile.good());
    ASSERT_TRUE(client.Remove(file.meta().name()));
}


/* Tests if there is a error when we can not import a file */
TEST(ManagerServiceTest, TestCheckIfCppFilesWereGenerated)
{
    ProtoClient client(grpc::CreateChannel(
                   "vetulus:4242", grpc::InsecureChannelCredentials()));

    string bytes = client.ReadFileAsString("/vetulus/protos/dog.proto");
    ProtoFile file;
    file.set_data(bytes);
    file.mutable_meta()->set_name("Dog2");
    client.Add(&file);

    ifstream headerfile("Dog2.pb.h");
    ifstream sourcefile("Dog2.pb.cc");

    ASSERT_TRUE(headerfile.good());
    ASSERT_TRUE(sourcefile.good());
    ASSERT_TRUE(client.Remove(file.meta().name()));
}


/* Tests Removing an imported protofile */
TEST(ManagerServiceTest, TestRemoveAProtofile)
{
    ProtoClient client(grpc::CreateChannel(
                   "vetulus:4242", grpc::InsecureChannelCredentials()));

    string bytes = client.ReadFileAsString("/vetulus/protos/dog.proto");
    ProtoFile file;
    file.set_data(bytes);
    file.mutable_meta()->set_name("Dog3");
    client.Add(&file);

    ASSERT_TRUE(client.Remove("Dog3"));
}


/* Tests if is not possible to upload same file twice */
TEST(ManagerServiceTest, TestUploadProtoTwice)
{
    ProtoClient client(grpc::CreateChannel(
                   "vetulus:4242", grpc::InsecureChannelCredentials()));

    string bytes = client.ReadFileAsString("/vetulus/protos/dog.proto");
    ProtoFile file;
    file.set_data(bytes);
    file.mutable_meta()->set_name("Dog0");
    client.Add(&file);
    ASSERT_FALSE(client.Add(&file));
    ASSERT_TRUE(client.Remove(file.meta().name()));
}


/* Tests if we can fork a new server from manager service */
TEST(ManagerServiceTest, TestForkServer)
{
  ProtoClient client(grpc::CreateChannel(
                 "vetulus:4242", grpc::InsecureChannelCredentials()));

  string bytes = client.ReadFileAsString("/vetulus/protos/dog.proto");
  ProtoFile file;
  file.set_data(bytes);
  file.mutable_meta()->set_name("Dog0");
  client.Add(&file);

  ADTService service;
  service.set_name("DogStack");
  service.set_description("A Dog stack service");
  service.set_adt("stack");
  service.set_address("127.0.0.1");
  service.set_port(42502);
  service.set_log_path("/tmp/dog_stack.log");

  ASSERT_TRUE(client.Start(&service));
  ASSERT_TRUE(client.Remove(file.meta().name()));
}


/* Tests if we can kill a running process */
TEST(ManagerServiceTest, TestKillServer)
{
  ProtoClient client(grpc::CreateChannel(
                 "vetulus:4242", grpc::InsecureChannelCredentials()));

  ADTService service;
  service.set_name("DogStack");
  service.set_description("A Dog stack service to kill");
  service.set_adt("stack");
  service.set_address("127.0.0.1");
  service.set_port(42502);
  service.set_log_path("/tmp/dog_stack.log");

  ASSERT_TRUE(client.Stop(&service));
}


/* Tests if we can list running services */
TEST(ManagerServiceTest, TestListServices)
{
  ProtoClient client(grpc::CreateChannel(
                 "vetulus:4242", grpc::InsecureChannelCredentials()));

  string bytes = client.ReadFileAsString("/vetulus/protos/dog.proto");
  ProtoFile file;
  file.set_data(bytes);
  file.mutable_meta()->set_name("Dog0");
  client.Add(&file);

  ADTService service;
  service.set_name("DogStack");
  service.set_description("A Dog stack service");
  service.set_adt("stack");
  service.set_address("127.0.0.1");
  service.set_port(42502);
  service.set_log_path("/tmp/dog_stack.log");

  ASSERT_TRUE(client.Start(&service));

  ListOptions opts;
  ListResponse running_list;
  running_list = client.ListServices(&opts);

  ASSERT_EQ(running_list.services_size(), 1);
  ASSERT_TRUE(client.Remove(file.meta().name()));
  ASSERT_TRUE(client.Stop(&service));
}


/* Tests if services list is empty */
TEST(ManagerServiceTest, TestListServicesIsEmpty)
{
  ProtoClient client(grpc::CreateChannel(
                 "vetulus:4242", grpc::InsecureChannelCredentials()));

  ListOptions opts;
  ListResponse running_list;
  running_list = client.ListServices(&opts);

  ASSERT_EQ(running_list.services_size(), 0);
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
