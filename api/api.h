
#include <pistache/endpoint.h>
#include <pistache/router.h>

#include "config.h"
#include "info.h"
#include "spdlog/spdlog.h"


namespace spd = spdlog;


using namespace Pistache;


class VetulusRouterHandler;


/*
 * VetulusRouter is an extension of the Pistache Rest::Router that allows
 * Vetulus to customize the way HTTP routing happens.
 */
class VetulusRouter: public Rest::Router {

    public:
        shared_ptr<VetulusRouterHandler> handler() const {
            return std::make_shared<VetulusRouterHandler>(*this);
        }
};


/*
 * VetulusRouterHandler customizes how the API router works. Every request
 * is routed at onRequest implementation. Within this implementation we can
 * log every request.
 */
class VetulusRouterHandler: public Http::Handler {

    public:
        VetulusRouterHandler(const VetulusRouter& router)
        {
            this->router = router;

            this->console = spd::get("Router");
            if(!this->console) {
                this->console = spd::stdout_color_mt("Router");
            }
        }

        void onRequest(const Http::Request& req, Http::ResponseWriter response)
        {
            auto resp = response.clone();
            auto result = router.route(req, std::move(resp));

            // Wait for Pull request to be accepted on Pistache to use
            // the function versionString(req.version()) as parameter
            this->console->info("{0} {1}",
                    methodString(req.method()), req.resource());

            if (result == Rest::Router::Status::NotFound) {

                response.send(Http::Code::Not_Found,
                              "Could not find a matching route bro!");
            }
        }

    private:
        std::shared_ptr<Tcp::Handler> clone() const {
            return std::make_shared<VetulusRouterHandler>(router);
        }

        VetulusRouter router;
        std::shared_ptr<spd::logger> console;
};


/*
 * Vetulus API interface definition.
 */
class VetulusAPI {

    public:
        VetulusAPI (APIConfigLoader config);
		void listen();

    protected:

        // Customized router to handle HTTP requests
        VetulusRouter router;

    private:
        void configure();
        void setRoutes();

        // The most simple response. Used by the / uri.
        void simpleResponse(const Rest::Request& request, Http::ResponseWriter response);

        InfoHandler info_handler;

        // Variables read from configuration file
        Port port;
        Address addr;
        int threads;

        // The endpoint from Pistache that really handles HTTP requests
        shared_ptr<Http::Endpoint> endpoint;
};
