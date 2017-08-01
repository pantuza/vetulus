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
#include <cstdio>

#include <gtest/gtest.h>

#include "config.h"


/* Tests loading a fake file as input */
TEST(ConfigurationTest, TestFakefileAsInput) {

    ConfigLoader loader;
    ASSERT_THROW(loader.load("fake.file"), invalid_argument);
}


/* Tests throwing an exception as a not implemented error */
TEST(ConfigurationTest, TestThrowExceptionOnSetConfigMethod) {

    /* Creates a fake configuration file */
    char filename[L_tmpnam];
    tmpnam(filename);
    FILE* file = fopen(filename, "w");
    fputs("Port *:4242", file);

    ConfigLoader loader;
    ASSERT_THROW(loader.load("api.conf"), runtime_error);

    fclose(file);  // Closes the temporary file. cstdio also removes it
}


int main(int argc, char **argv) {

    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
