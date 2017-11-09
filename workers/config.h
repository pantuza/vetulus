/*
 * Copyright 2017 <Gustavo Pantuza>
 *
 * ============================================================================
 *
 *       Filename:  config.h
 *
 *    Description:  Vetulus Workers specific configuration class. Inherits from
 *                  generc configuration class from config module.
 *
 *        Version:  1.0
 *        Created:  11/09/2017 15:02:32
 *       Compiler:  g++
 *
 *         Author:  Gustavo Pantuza (gustavopantuza@gmail.com)
 *   Organization:  Computer science community
 *
 * ============================================================================
 */

#ifndef WORKERS_CONFIG_H_
#define WORKERS_CONFIG_H_

#include "../config/config.h"


using std::string;


class WorkersConfigLoader: public ConfigLoader {
 public:
    string threads;

 private:
    void set_config() {
        this->threads = this->variables["Threads"][0];
    }
};

#endif  // WORKERS_CONFIG_H_
