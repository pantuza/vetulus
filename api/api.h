
#include <pistache/endpoint.h>
#include <pistache/router.h>

#include "config.h"
#include "info.h"


using namespace Pistache;


class VetulusAPI: public Http::Endpoint {

    public:
        VetulusAPI (APIConfigLoader config);
		void listen();

    protected:
        Rest::Router router;

    private:
        void configure();
        void load_routes();
        void simpleResponse(const Rest::Request& request, Http::ResponseWriter response);

        InfoHandler info_handler;
        Port port;
        Address addr;
};
