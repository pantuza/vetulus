/*
 * Copyright 2017 <Gustavo Pantuza>
 *
 * ============================================================================
 *
 *       Filename:  test_stack_server.cc
 *
 *    Description:  Test program for the gRPC Stack service
 *
 *        Version:  0.1
 *        Created:  12/13/2017 15:01:52 PM
 *       Compiler:  g++
 *
 *         Author:  Gustavo Pantuza (gustavopantuza@gmail.com)
 *   Organization:  Computer science community
 *
 * ============================================================================
 */

#ifndef SERVICE_STACK_TEST_H_
#define SERVICE_STACK_TEST_H_

#include <iostream>
#include <string>
#include <sstream>

#include <gtest/gtest.h>

#include "./config.h"
#include "./stack_client.h"



/* Tests Pushing an Item to the Stack service */
TEST(StackServiceTest, TestPushItem)
{
    StackClient client(grpc::CreateChannel(
                   "vetulus:42500", grpc::InsecureChannelCredentials()));
    Dog item;
    item.set_name("Test item");
    ASSERT_TRUE(client.Push(item));
}


/* Tests Poping an Item from the Stack service */
TEST(StackServiceTest, TestPopItem)
{
    StackClient client(grpc::CreateChannel(
                       "vetulus:42500", grpc::InsecureChannelCredentials()));
    ASSERT_TRUE(dynamic_cast<Dog*>(client.Pop()) != nullptr);
}


/* Tests checking the Stack size */
TEST(StackServiceTest, TestStackSize)
{
    StackClient client(grpc::CreateChannel(
                   "vetulus:42500", grpc::InsecureChannelCredentials()));
    Dog junior;
    junior.set_name("Jorge Junior");
    Dog nina;
    nina.set_name("Nina");

    ASSERT_EQ(client.Size()->value(), 0);
    client.Push(junior);
    ASSERT_EQ(client.Size()->value(), 1);
    client.Push(nina);
    ASSERT_EQ(client.Size()->value(), 2);
    client.Pop();
    ASSERT_EQ(client.Size()->value(), 1);
}


/* Tests checking if the stack is empty */
TEST(StackServiceTest, TestStackIsNotEmpty)
{
    StackClient client(grpc::CreateChannel(
                   "vetulus:42500", grpc::InsecureChannelCredentials()));
    Dog junior;
    junior.set_name("Jorge Junior");
    client.Push(junior);
    ASSERT_FALSE(client.IsEmpty()->value());
}


/* Tries to pop an item when the stack is empty */
TEST(StackServiceTest, TestStackCantPop)
{
    StackClient client(grpc::CreateChannel(
                   "vetulus:42500", grpc::InsecureChannelCredentials()));
    client.Clear();
    Dog* dog = client.Pop();
    ASSERT_TRUE(dog == NULL);
}


/* Tests if the stack were cleared */
TEST(StackServiceTest, TestStackClear)
{
    StackClient client(grpc::CreateChannel(
                   "vetulus:42500", grpc::InsecureChannelCredentials()));
    Dog calvin;
    calvin.set_name("Calvim");
    client.Push(calvin);
    ASSERT_FALSE(client.IsEmpty()->value());

    client.Clear();
    ASSERT_TRUE(client.IsEmpty()->value());

}


/* Tests if we receive false when we try to clear an empty stack */
TEST(StackServiceTest, TestStackCantClear)
{
    StackClient client(grpc::CreateChannel(
                   "vetulus:42500", grpc::InsecureChannelCredentials()));
    client.Clear();
    StackBoolResponse* response = client.Clear();
    ASSERT_FALSE(response->value());
}


/* Tests to get the top of the stack */
TEST(StackServiceTest, TestGetTopOfStack)
{
    StackClient client(grpc::CreateChannel(
                   "vetulus:42500", grpc::InsecureChannelCredentials()));
    client.Clear();
    Dog floquinho;
    floquinho.set_name("Floquinho");
    client.Push(floquinho);

    ASSERT_FALSE(client.IsEmpty()->value());
    Dog* response = client.Top();
    ASSERT_EQ(response->name(), floquinho.name());
    ASSERT_GT(client.Size()->value(), 0);
}


/* Tries to get the top item when the stack is empty */
TEST(StackServiceTest, TestCantGetTopOfStack)
{
    StackClient client(grpc::CreateChannel(
                   "vetulus:42500", grpc::InsecureChannelCredentials()));
    client.Clear();
    Dog* dog = client.Top();
    ASSERT_TRUE(dog == NULL);
}


int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);

    string config_file = "/etc/vetulus/services/stack_client.conf";

    if (argc > 1) {
        config_file = argv[1];
    }

    StackConfigLoader config;
    config.load(config_file);

    ostringstream config_str;

    StackClient client(grpc::CreateChannel(
                   "vetulus:42500", grpc::InsecureChannelCredentials()));
    client.Clear();

    return RUN_ALL_TESTS();
}


#endif  // SERVICE_STACK_TEST_H_
