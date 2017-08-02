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

#include "config.h"
#include "info.h"
#include "api.h"


using namespace Pistache;


void VetulusAPI::configure ()
{
    auto opts = Http::Endpoint::options().threads(2);
	this->init(opts);
}


void VetulusAPI::load_routes ()
{

}


void VetulusAPI::listen ()
{
	this->setHandler(this->router.handler());

    cout << "Vetulus API listening at " << this->port << endl;
    this->serve();
    this->shutdown();
}


int main(int argc, char* argv[]) {

    string config_file = "/etc/vetulus/api.conf";

    if(argc > 1) {
        config_file = argv[1];
    }

    APIConfigLoader loader;
    loader.load(config_file);

    Address addr(Ipv4::any(), Port(loader.port));
    VetulusAPI server(addr);

    server.configure();
    server.listen();
}
