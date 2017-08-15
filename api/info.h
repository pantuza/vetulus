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
#include <pistache/router.h>

#include "json.hpp"


using json = nlohmann::json;

using namespace Pistache;


/**
 * Class to describe the most basic information about the Vetulus API
 */
class InfoHandler {

    public:
        void setRoutes(Rest::Router& router) {
            using namespace Rest;

            Routes::Get(
                router,
                "/info",
                Routes::bind(&InfoHandler::getInfo, this)
            );
        }


        /*
         * Basic Vetulus API information
         */
        void getInfo(const Rest::Request& request,
                     Http::ResponseWriter response) {

            json data;
            data["server"] = "Vetulus API";
            data["version"] = {0, 1, 0};
            data["description"] = "Your data structure as a service";
            data["project"] = "https://github.com/pantuza/vetulus";
            data["license"] = "General Public License v3";
            data["Language"] = "C++11";

            response.send(Http::Code::Ok, data.dump());
        }
};
