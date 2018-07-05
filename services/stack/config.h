/*
 * Copyright 2017 <Gustavo Pantuza>
 *
 * ============================================================================
 *
 *       Filename:  config.cc
 *
 *    Description:  Vetulus Stack service specific configuration class.
 *                  Inherits from generic configuration class from
 *                  config module.
 *
 *        Version:  0.1
 *        Created:  12/05/2017 12:00:32
 *       Compiler:  g++
 *
 *         Author:  Gustavo Pantuza (gustavopantuza@gmail.com)
 *   Organization:  Computer science community
 *
 * ============================================================================
 */


#ifndef SERVICES_STACK_CONFIG_H_
#define SERVICES_STACK_CONFIG_H_


#include <stdlib.h>
#include <string>

// #include "../../config/config.h"
#include "vetulus/config.h"


using std::string;


class StackConfigLoader: public ConfigLoader {
 public:
    string port;
    string addr;

 private:
    void set_config() {
        this->port = this->variables["Port"][0];
        this->addr = this->variables["Addr"][0];
    }
};

#endif  // SERVICES_STACK_CONFIG_H_
