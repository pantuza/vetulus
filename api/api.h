
#include <signal.h>

#include <pistache/endpoint.h>
#include <pistache/router.h>

#include "config.h"
#include "info.h"


using namespace Pistache;


class VetulusAPI {

    public:
        VetulusAPI (APIConfigLoader config);
		void listen();

    protected:
        Rest::Router router;

    private:
        void configure();
        void setRoutes();
        void setListeners();
        static void sigintCallback(int signal);

        void simpleResponse(const Rest::Request& request, Http::ResponseWriter response);

        InfoHandler info_handler;
        Port port;
        Address addr;
        int threads;
        shared_ptr<Http::Endpoint> endpoint;
};
