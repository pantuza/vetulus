/*
 * ============================================================================
 *
 *       Filename:  test_dispatcher.cc
 *
 *    Description:  Tests the VetulusDispatcher class
 *
 *        Version:  1.0
 *        Created:  06/22/2018 02:41:12 PM
 *       Compiler:  gcc
 *
 *         Author:  Gustavo Pantuza (gustavopantuza@gmail.com)
 *   Organization:  Computer science community
 *
 * ============================================================================
 */


#include <gtest/gtest.h>

#include "dispatcher.h"


using dispatcher::VetulusDispatcher;



/* Tests a true condition */
TEST(DispatcherTest, TestTrue)
{
  ASSERT_TRUE(true);
}




int
main (int argc, char* argv[])
{
    ::testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}
