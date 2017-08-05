/*
 * ============================================================================
 *
 *       Filename:  test_api.cc
 *
 *    Description:  Test program for basic API requests
 *
 *        Version:  0.1
 *        Created:  07/28/2017 11:07:52 PM
 *       Compiler:  g++
 *
 *         Author:  Gustavo Pantuza (gustavopantuza@gmail.com)
 *   Organization:  Computer science community
 *
 * ============================================================================
 */

#include <cstdio>

#include <gtest/gtest.h>
#include <pistache/client.h>


using namespace Pistache;


/* Tests loading a fake file as input */
TEST(ConfigurationTest, TestFakefileAsInput) {

    Http::Client client;
    client.init(Http::Client::options());

    auto resp = client.get("localhost:4242").send();
    resp.then([&](Http::Response response) {
        ASSERT_EQ(response.code(), Http::Code::Ok);
    }, Async::IgnoreException);
}


int main(int argc, char **argv) {

    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
