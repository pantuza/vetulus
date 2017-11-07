
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


class VetulusRouterHandler: public Http::Handler {

    public:
        VetulusRouterHandler(const VetulusRouter& router)
        {
            this->router = router;
            std::cout << "RouterHandler constructor" << std::endl;
        }

        void onRequest(const Http::Request& req, Http::ResponseWriter response)
        {
            auto resp = response.clone();
            auto result = router.route(req, std::move(resp));

            std::cout << "onRequest log" << std::endl;

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
};


class VetulusAPI {

    public:
        VetulusAPI (APIConfigLoader config);
		void listen();

    protected:
        VetulusRouter router;

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
