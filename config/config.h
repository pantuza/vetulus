#include <string>
#include <stdexcept>
#include <vector>
#include <map>


using namespace std;


/*
 * Generic configuration loader class. Each module inherits from this class
 * and implements its own set_config method to load as class members variables
 * that configures the module
 */
class ConfigLoader {

    public:
        void load (string filename);

    protected:
        /* Class member to store file parsed variables */
        map<string, vector<string> > variables;

    private:
        virtual void set_config ();
};
