/*
 * ============================================================================
 *
 *       Filename:  main_api.cpp
 *
 *    Description:  Main execution of the API server
 *
 *        Version:  1.0
 *        Created:  07/26/2017 12:47:30 AM
 *       Compiler:  g++
 *
 *         Author:  Gustavo Pantuza (gustavopantuza@gmail.com),
 *   Organization:  Computer science community
 *
 * ============================================================================
 */

#include <pistache/endpoint.h>

#include "../config/config.h"


using namespace Pistache;


class HelloHandler : public Http::Handler {

    public:

        HTTP_PROTOTYPE(HelloHandler)

        void onRequest(const Http::Request& request, Http::ResponseWriter response) {
             response.send(Http::Code::Ok, "Hello, World");
        }
};


int main() {

    ConfigLoader loader;
    loader.load("api.conf");

    cout << "Vetulus API listening at " << loader.port << endl;
    Http::listenAndServe<HelloHandler>(loader.port);
}

