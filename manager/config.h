/*
 * Copyright 2017 <Gustavo Pantuza>
 *
 * ============================================================================
 *
 *       Filename:  config.h
 *
 *    Description:  Vetulus service specific configuration class.
 *                  Inherits from generic configuration class from
 *                  config module.
 *
 *        Version:  0.1
 *        Created:  01/05/2018 23:44:12
 *       Compiler:  g++
 *
 *         Author:  Gustavo Pantuza (gustavopantuza@gmail.com)
 *   Organization:  Computer science community
 *
 * ============================================================================
 */


#ifndef MANAGER_CONFIG_H_
#define MANAGER_CONFIG_H_


#include <stdlib.h>
#include <string>

#include "../../config/config.h"


using std::string;


class ProtoConfigLoader: public ConfigLoader {
 public:
    string port;
    string addr;

 private:
    void set_config() {
        this->port = this->variables["Port"][0];
        this->addr = this->variables["Addr"][0];
    }
};

#endif  // MANAGER_CONFIG_H_
