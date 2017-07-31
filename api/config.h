/*
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

#include <stdlib.h>
#include <string>

#include "../config/config.h"


using namespace std;


class APIConfigLoader: public ConfigLoader {

    public:
        string port;

    private:
        void set_config () {

            this->port = this->variables["Port"][0];
        }
};
