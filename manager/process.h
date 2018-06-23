/*
 * Copyright 2018 <Gustavo Pantuza>
 *
 * ============================================================================
 *
 *       Filename:  process.h
 *
 *    Description:  Header with types and forked process control
 *
 *        Version:  1.0
 *        Created:  21/06/2018 08:00:32 PM
 *       Compiler:  g++
 *
 *         Author:  Gustavo Pantuza (gustavopantuza@gmail.com)
 *   Organization:  Computer science community
 *
 * ============================================================================
 */


#ifndef _MANAGER_PROCESS_H
#define _MANAGER_PROCESS_H


#include <sys/types.h>
#include <unistd.h>

#include <cerrno>
#include <csignal>
#include <string>
#include <list>

#include "./spdlog/spdlog.h"

using std::string;
using std::list;
using std::strerror;
using std::shared_ptr;


namespace processes {

/**
 * Struct to store data from one single forked process
 */
struct vetulus_process {

  pid_t process_pid;  // Process ID on system

  pid_t parent_pid;  // Parent process ID on system

  int port; // Port that process is listening

  string name; // The humanized name of the process
};



/* Single Vetulus process type definition */
typedef vetulus_process VetulusProcess_t;



/**
 * Class to control life cycle of Vetulus processes and store its informations
 */
class VetulusProcess {

 public:
  VetulusProcess ()
  {
    this->console = spdlog::get("Process");
    if (!this->console) {
        this->console = spdlog::stdout_color_mt("Process");
    }
  }

  /**
   * Adds a new process on the process list if it does not exists
   */
  bool Add (VetulusProcess_t process)
  {
    for (auto i : process_list) {
      if (i.process_pid == process.process_pid || i.name == process.name) {

        console->info("Process with name {0} already exists", process.name);
        return false;
      }
    }

    process_list.push_back(process);
    console->info("Add process pid {0} to process list", process.process_pid);

    return true;
  }

  /**
   * Tries to remove a process from process list and killing it by its pid
   */
  bool Remove (pid_t pid)
  {
    for (auto i = process_list.begin(); i != process_list.end(); i++) {

      if (i->process_pid == pid) {
        if (kill_process(pid)) {

          process_list.erase(i);
          return true;
        }
      }
    }
    console->info("Can't find process with pid {0}", pid);
    return false;
  }

  /**
   * Tries to remove a process from process list by its name and killing
   * it by its pid
   */
  bool Remove (const string name)
  {
    for (auto i = process_list.begin(); i != process_list.end(); i++) {

      if (i->name == name) {
        if (kill_process(i->process_pid)) {

            process_list.erase(i);
            return true;
        }
      }
    }
    console->info("Can't find process with name {0}", name);
    return false;
  }

  /**
   * Removes all processes in the process list
   */
  bool RemoveAll ()
  {
    for (auto i = process_list.begin(); i != process_list.end(); i++) {

      if (! kill_process(i->process_pid)) {
        return false;
      }
      process_list.erase(i);
    }

    return true;
  }

 private:

  /* Logging used for Processes operations */
  shared_ptr<spdlog::logger> console;

  /* A list of running processes */
  list<VetulusProcess_t> process_list;

  bool kill_process (pid_t pid)
  {
    int killed = kill(pid, SIGTERM);

    if (killed == 0) {
      console->info("Killed process pid {0}", pid);
      return true;

    } else if(errno == EINVAL || errno == ESRCH || errno == EPERM) {

      this->console->error(strerror(errno));
    }
    return false;
  }

};

};

#endif // _MANAGER_PROCESS_H
