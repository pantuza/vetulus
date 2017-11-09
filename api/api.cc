/*
 * Copyright 2017 <Gustavo Pantuza>
 *
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

#include <signal.h>

#include <pistache/endpoint.h>

#include "./api.h"
#include "./json.hpp"
#include "./spdlog/spdlog.h"


using json = nlohmann::json;

namespace spd = spdlog;

using namespace Pistache;



/**
 * Callback to handle SIGINT signal when caught
 */
static void sigintCallback(int signal)
{
    cout << "Caught keyboard interruption. Shuting down Vetulus API" << endl;
    exit(1);
}



/**
 * Vetulus API Constructor. We create a Pistache HTTP Endpoint
 */
VetulusAPI::VetulusAPI(APIConfigLoader config)
    : port(Port(stoi(config.port)))
    , addr(config.addr, port)
    , threads(stoi(config.threads))
    , endpoint(make_shared<Http::Endpoint>(addr))
{
    this->configure();
    this->setRoutes();
}


/**
 * Configures the Web server based on configuration file
 */
void VetulusAPI::configure()
{
    auto opts = Http::Endpoint::options().threads(this->threads).flags(
            Tcp::Options::InstallSignalHandler);

    this->endpoint->init(opts);
}


/**
 * Set L7 routes handled by Pistache
 */
void VetulusAPI::setRoutes()
{
    using namespace Rest;

    Routes::Get(
        this->router,
        "/",
        Routes::bind(&VetulusAPI::simpleResponse, this));

    /*
     * Every new API goes here. A new class should implement the setRoutes
     * method to assign its own routes and handlers callbacks
     */
    this->info_handler.setRoutes(this->router);
}


void VetulusAPI::simpleResponse(const Rest::Request& request,
                                Http::ResponseWriter response)
{
    json data;
    data["status"] = 200;
    data["body"] = "Hello Nurse";
    string data_str = data.dump();

    response.send(Http::Code::Ok, data_str);
}


/**
 * Enters in listen mode and waits for connections
 */
void VetulusAPI::listen()
{
    this->endpoint->setHandler(this->router.handler());

    cout << "Vetulus API listening at " << this->addr.host()
         << ":" << this->addr.port() << " with "
         << this->threads << " threads" << endl;

    this->endpoint->serve();
    this->endpoint->shutdown();
}



/**
 * Main execution of the API binary
 */
int main(int argc, char* argv[]) {
    string config_file = "/etc/vetulus/api.conf";

    if (argc > 1) {
        config_file = argv[1];
    }

    signal(SIGINT, sigintCallback);

    APIConfigLoader config;
    config.load(config_file);

    VetulusAPI server(config);

    // Console logger with color
    auto console = spd::stdout_color_mt("console");
    console->info("Welcome to Vetulus API!");

    server.listen();

    return EXIT_SUCCESS;
}
