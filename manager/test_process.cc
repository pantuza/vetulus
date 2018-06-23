/*
 * ============================================================================
 *
 *       Filename:  test_process.cc
 *
 *    Description:  Tests the VetulusProcess class
 *
 *        Version:  1.0
 *        Created:  06/22/2018 09:57:46 PM
 *       Compiler:  gcc
 *
 *         Author:  Gustavo Pantuza (gustavopantuza@gmail.com)
 *   Organization:  Computer science community
 *
 * ============================================================================
 */

#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>

#include <chrono>
#include <thread>

#include <gtest/gtest.h>

#include "process.h"

using std::chrono::milliseconds;
using std::this_thread::sleep_for;

using processes::VetulusProcess;
using processes::VetulusProcess_t;



/* Tests adding a new process */
TEST(ProcessTest, TestAddProcess)
{
  VetulusProcess_t process;
  process.name = "proc_0";
  process.process_pid = 1;

  VetulusProcess processes;
  ASSERT_TRUE(processes.Add(process));
  ASSERT_EQ(processes.Size(), 1);
}


/* Tests adding a duplicated process by its pid */
TEST(ProcessTest, TestAddDuplicatedPid)
{
  VetulusProcess_t process_0;
  process_0.name = "proc_0";
  process_0.process_pid = 1;

  VetulusProcess_t process_1;
  process_1.name = "proc_1";
  process_1.process_pid = 1;

  VetulusProcess processes;
  ASSERT_TRUE(processes.Add(process_0));
  ASSERT_FALSE(processes.Add(process_1));
  ASSERT_EQ(processes.Size(), 1);
}


/* Tests adding a duplicated process by its name */
TEST(ProcessTest, TestAddDuplicatedName)
{
  VetulusProcess_t process_0;
  process_0.name = "proc_0";
  process_0.process_pid = 1;

  VetulusProcess_t process_1;
  process_1.name = "proc_0";
  process_1.process_pid = 2;

  VetulusProcess processes;
  ASSERT_TRUE(processes.Add(process_0));
  ASSERT_FALSE(processes.Add(process_1));
  ASSERT_EQ(processes.Size(), 1);
}


/* Tests removing process by pid */
TEST(ProcessTest, TestRemoveProcessByPid)
{
  VetulusProcess processes;

  pid_t pid = fork();

  if(pid == 0) {
    int ten_seconds = 10000;
    sleep_for(milliseconds(ten_seconds));
    exit(EXIT_SUCCESS);
  } else if (pid > 0) {

    VetulusProcess_t process;
    process.name = "proc_0";
    process.process_pid = pid;

    processes.Add(process);
    ASSERT_EQ(processes.Size(), 1);
    ASSERT_TRUE(processes.Remove(pid));
    ASSERT_EQ(processes.Size(), 0);
  }
}


/* Tests removing process by name */
TEST(ProcessTest, TestRemoveProcessByName)
{
  VetulusProcess processes;

  pid_t pid = fork();

  if(pid == 0) {
    int ten_seconds = 10000;
    sleep_for(milliseconds(ten_seconds));
    exit(EXIT_SUCCESS);
  } else if (pid > 0) {

    VetulusProcess_t process;
    process.name = "proc_0";
    process.process_pid = pid;

    processes.Add(process);
    ASSERT_EQ(processes.Size(), 1);
    ASSERT_TRUE(processes.Remove(process.name));
    ASSERT_EQ(processes.Size(), 0);
  }
}


/* Tests removing an unexistent pid */
TEST(ProcessTest, TestRemoveUnexistentPid)
{
  VetulusProcess processes;
  ASSERT_FALSE(processes.Remove(-1));
}


/* Tests removing an unexistent process name */
TEST(ProcessTest, TestRemoveUnexistentProcessName)
{
  VetulusProcess processes;
  ASSERT_FALSE(processes.Remove("fake_proc"));
}


/* Tests removing all processes */
TEST(ProcessTest, TestRemoveAllProcesses)
{
  VetulusProcess processes;

  pid_t pid = fork();

  if(pid == 0) {
    int ten_seconds = 10000;
    sleep_for(milliseconds(ten_seconds));
    exit(EXIT_SUCCESS);
  } else if (pid > 0) {

    VetulusProcess_t process;
    process.name = "proc_0";
    process.process_pid = pid;

    processes.Add(process);
    ASSERT_EQ(processes.Size(), 1);
    ASSERT_TRUE(processes.RemoveAll());
    ASSERT_EQ(processes.Size(), 0);
  }
}



int
main (int argc, char* argv[])
{
    ::testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}
