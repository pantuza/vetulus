/*
 * Copyright 2017 <Gustavo Pantuza>
 *
 * ============================================================================
 *
 *       Filename:  pool.h
 *
 *    Description:  Header file of the Thread Pool class
 *
 *        Version:  1.0
 *        Created:  11/09/2017 14:56:13
 *       Compiler:  g++
 *
 *         Author:  Gustavo Pantuza (gustavopantuza@gmail.com)
 *   Organization:  Computer Science community
 *
 * ============================================================================
 */


#ifndef WORKERS_POOL_H_
#define WORKERS_POOL_H_


#include <vector>
#include <queue>
#include <thread>
#include <functional>
#include <sstream>
#include <string>

#include "./spdlog/spdlog.h"

using std::vector;
using std::queue;
using std::thread;
using std::function;
using std::string;

namespace spd = spdlog;


class ThreadPool {
 public:
    explicit ThreadPool(unsigned int n_threads);
    void arise();
    void die();
    void Add(function<void()>);

 private:
    unsigned int n_threads;
    vector<thread> workers;
    queue<function<void()>> tasks;

    void work(int index);
    string getThreadID(thread& thr);

    std::shared_ptr<spd::logger> console;
};

#endif  // WORKERS_POOL_H_
