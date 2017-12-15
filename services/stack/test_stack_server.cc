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
                   "172.17.0.2:42500", grpc::InsecureChannelCredentials()));
    Dog item;
    item.set_name("Test item");
    ASSERT_TRUE(client.Push(item));
}


/* Tests Poping an Item from the Stack service */
TEST(StackServiceTest, TestPopItem)
{
    StackClient client(grpc::CreateChannel(
                       "127.0.0.1:42500", grpc::InsecureChannelCredentials()));
    ASSERT_TRUE(dynamic_cast<Dog*>(client.Pop()) != nullptr);
}


/* Tests checking the Stack size */
TEST(StackServiceTest, TestStackSize)
{
    StackClient client(grpc::CreateChannel(
                   "172.17.0.2:42500", grpc::InsecureChannelCredentials()));
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

    return RUN_ALL_TESTS();
}


#endif  // SERVICE_STACK_TEST_H_
