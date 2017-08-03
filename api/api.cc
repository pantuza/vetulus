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

#include "api.h"


using namespace Pistache;


VetulusAPI::VetulusAPI (APIConfigLoader config)
    : port(Port(stoi(config.port))),
      addr(Ipv4::any(), port),
      Endpoint(addr)
{
    this->configure();
    this->load_routes();
}


void VetulusAPI::configure ()
{
    auto opts = Http::Endpoint::options().threads(2).flags(
            Tcp::Options::InstallSignalHandler);

	this->init(opts);
}


void VetulusAPI::simpleResponse (const Rest::Request& request, Http::ResponseWriter response)
{
     response.send(Http::Code::Ok, "{\"status\": 200, \"body\": \"Hello, World\"}");
}

void VetulusAPI::load_routes ()
{
    using namespace Rest;

    Routes::Get(
        this->router,
        "/",
        Routes::bind(&VetulusAPI::simpleResponse, this)
    );
}


void VetulusAPI::listen ()
{
	this->setHandler(this->router.handler());

    cout << "Vetulus API listening at " << this->addr.host() << ":" << this->addr.port() << endl;
    this->serve();
    this->shutdown();
}


int main(int argc, char* argv[]) {

    string config_file = "/etc/vetulus/api.conf";

    if(argc > 1) {
        config_file = argv[1];
    }

    APIConfigLoader config;
    config.load(config_file);

    VetulusAPI server(config);

    server.listen();
}
