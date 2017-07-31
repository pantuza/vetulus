/*
 * ============================================================================
 *
 *       Filename:  config.cc
 *
 *    Description:  Generic configuration parser
 *
 *        Version:  1.0
 *        Created:  07/27/2017 12:31:38 AM
 *       Compiler:  g++
 *
 *         Author:  Gustavo Pantuza (gustavopantuza@gmail.com)
 *   Organization:  Computer Science community
 *
 * ============================================================================
 */

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <sstream>

#include "config.h"


using namespace std;


/*
 * Parses text from a givem file. It reads file content into a map of string
 * vectors. Vetulus configuration file format must be in the following format:
 *
 * Port *:4242
 * Users Gustavo Alice Bob
 *
 * The key of configuration will be the first string. And the value is a vector
 * of string of the current line. Each line must represent one configuration.
 */
void ConfigLoader::load (string filename) {

    string name;
    string value;
    string tmp_value;

    ifstream ifile(filename);

    if(ifile.is_open()) {
        getline(ifile, name, ' ');
        getline(ifile, value);

        while(ifile) {

            istringstream istr(value);
            vector<string> values;
            while(istr >> tmp_value) {
                values.push_back(tmp_value);
            }

            this->variables[name] = values;

            getline(ifile, name, ' ');
            getline(ifile, value);
        }
        ifile.close();

        /* Calls the set_config. This method should exist at inheritor class */
        this->set_config();

    } else {
        throw invalid_argument("Can't open configuration file: " + filename);
    }
}


/*
 * This method should be overridden by child class. Each class should write
 * its own configuration specific needs. For the generic class this method
 * raises a runtime exception.
 */
void ConfigLoader::set_config ()
{
    throw runtime_error("Generic ConfigLoader can not set variables");
}
