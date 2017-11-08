/*
 * Copyright 2017 <Gustavo Pantuza>
 *
 * ============================================================================
 *
 *       Filename:  config.cc
 *
 *    Description:  Vetulus API specific configuration class. Inherits from
 *                  generic configuration class from config module.
 *
 *        Version:  0.1
 *        Created:  07/31/2017 12:56:37
 *       Compiler:  g++
 *
 *         Author:  Gustavo Pantuza (gustavopantuza@gmail.com)
 *   Organization:  Computer science community
 *
 * ============================================================================
 */


#ifndef API_CONFIG_H_
#define API_CONFIG_H_


#include <stdlib.h>
#include <string>

#include "../config/config.h"


using std::string;


class APIConfigLoader: public ConfigLoader {
 public:
    string port;
    string addr;
    string threads;

 private:
    void set_config() {
        this->port = this->variables["Port"][0];
        this->addr = this->variables["Addr"][0];
        this->threads = this->variables["Threads"][0];
    }
};

#endif  // API_CONFIG_H_
