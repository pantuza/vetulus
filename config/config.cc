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

void
ConfigLoader::load (string filename) {

    cout << "Loading configuration" << endl;

    map<string, vector<string>> variables;
    string name;
    string value;
    string tmp_value;

    ifstream ifile("api.conf");

    if(ifile.is_open()) {
        getline(ifile, name, ' ');
        getline(ifile, value);

        while(ifile) {

            istringstream istr(value);
            vector<string> values;
            while(istr >> tmp_value) {
                values.push_back(tmp_value);
            }

            variables[name] = values;

            getline(ifile, name, ' ');
            getline(ifile, value);
        }
        ifile.close();

        for(auto& item: variables) {
            cout << item.first << ": ";
            for(auto value: item.second) {
                cout << value << " ";
            }
            cout << endl;
        }
    } else {
        cout << "Can't open configuration file" << endl;
    }
}
