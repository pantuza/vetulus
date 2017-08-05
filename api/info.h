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


using namespace Pistache;


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

        void getInfo(const Rest::Request& request, Http::ResponseWriter response) {

             response.send(Http::Code::Ok, "{\"status\": 200, \"body\": \"Info message\"}");
        }
};
