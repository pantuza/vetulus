
#include <pistache/endpoint.h>
#include <pistache/router.h>


using namespace Pistache;


class VetulusAPI: public Http::Endpoint {

    public:
        void configure();
		void listen();

    protected:
        Router router;

    private:
        void load_routes();
};
