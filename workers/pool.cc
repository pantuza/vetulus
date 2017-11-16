/*
 * Copyright 2017 <Gustavo Pantuza>
 *
 * ============================================================================
 *
 *       Filename:  pool.cc
 *
 *    Description:  Thread Pool class implementation
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

#include <iostream>
#include <sstream>
#include <string>

#include "./spdlog/spdlog.h"

#include "./pool.h"

using namespace std;

namespace spd = spdlog;


ThreadPool::ThreadPool(unsigned int n_threads)
: n_threads(n_threads)
{
    this->console = spd::stdout_color_mt("ThreadPool");
}


void ThreadPool::arise()
{
    for (int i = 0; i < this->n_threads; i++)
    {
        this->workers.push_back(thread([=] {this->work(i);}));
    }
    std::this_thread::sleep_for(std::chrono::seconds(10));
    this->die();
}


void ThreadPool::work(int index)
{
    this->console->info("Starting thread {0}",
                        this->getThreadID(this->workers[index]));

    while (!this->tasks.empty()) {
        function<void()> fn = this->tasks.front();
        this->tasks.pop();

        fn();
    }

    // dequeue a function
    // Run it
    // Return its result
}


string ThreadPool::getThreadID(thread& thr)
{
    ostringstream thread_id;
    thread_id << thr.get_id();

    return thread_id.str();
}


void ThreadPool::Add(function<void()> fn)
{
    this->tasks.push(fn);
}


void ThreadPool::die()
{
    for (auto& thread : this->workers) {
        if (thread.joinable()) {
            this->console->info("Joining thread {0}",
                                this->getThreadID(thread));

            thread.join();
        }
    }
}
