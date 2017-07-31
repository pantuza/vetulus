/*
 * ============================================================================
 *
 *       Filename:  test_config.cc
 *
 *    Description:  Test program for generic configuration class
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

#include <stdexcept>

#include <gtest/gtest.h>

#include "config.h"


/* Tests loading a fake file as input */
TEST(ConfigurationTest, TestFakefileAsInput) {

    ConfigLoader loader;
    ASSERT_THROW(loader.load("fake.file"), invalid_argument);
}


/* Tests throwing an exception as a not implemented error */
TEST(ConfigurationTest, TestThrowExceptionOnSetConfigMethod) {

    ConfigLoader loader;
    ASSERT_THROW(loader.load("api.conf"), runtime_error);
}


int main(int argc, char **argv) {

    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
