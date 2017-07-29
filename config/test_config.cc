/*
 * =====================================================================================
 *
 *       Filename:  test_config.cc
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  07/28/2017 11:07:52 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */
#include <stdlib.h>

#include <gtest/gtest.h>

#include "config.h"

// Tests configuration class
TEST(ConfigurationTest, TestsIf42) {
    
    ConfigLoader loader;
    loader.load("api.conf");

    ASSERT_TRUE(true);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
