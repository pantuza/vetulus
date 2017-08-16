
#include <pistache/endpoint.h>
#include <pistache/router.h>

#include "config.h"
#include "info.h"
#include "spdlog/spdlog.h"


namespace spd = spdlog;


using namespace Pistache;


class VetulusRouterHandler;


class VetulusRouter: public Rest::Router {

    public:
        shared_ptr<VetulusRouterHandler> handler() const {
            return std::make_shared<VetulusRouterHandler>(*this);
        }
};


class VetulusRouterHandler: public Rest::Private::RouterHandler {

    public:
        VetulusRouterHandler(const VetulusRouter& router)
            : Rest::Private::RouterHandler((Rest::Router&) router)
        {
            this->router = router;
            // Console logger with color
            auto console = spd::stdout_color_mt("console_0");
            console->info("Router constructor");
        }

        void onRequest(const Http::Request& req, Http::ResponseWriter response)
        {
            auto resp = response.clone();
            auto result = router.route(req, std::move(resp));

            // Console logger with color
            auto console = spd::stdout_color_mt("console_1");
            console->info("OnRequest by router");

            if (result == Rest::Router::Status::NotFound) {

                response.send(Http::Code::Not_Found,
                              "Could not find a matching route bro!");
            }
        }

    protected:
        VetulusRouter router;
};


class VetulusAPI {

    public:
        VetulusAPI (APIConfigLoader config);
		void listen();

    protected:
        Rest::Router router;

    private:
        void configure();
        void setRoutes();

        void simpleResponse(const Rest::Request& request, Http::ResponseWriter response);

        InfoHandler info_handler;
        Port port;
        Address addr;
        int threads;
        shared_ptr<Http::Endpoint> endpoint;
};
