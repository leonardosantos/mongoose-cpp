#ifdef _MSC_VER
#include <windows.h>
#else
#include <unistd.h>
#endif
#include <stdlib.h>
#include <signal.h>
#include <mongoose-cpp/Server.h>
#include <mongoose-cpp/WebController.h>

using namespace std;
using namespace Mongoose;

class MyController : public WebController
{
    public: 

        void setup()
        {
            route("GET", "/hello", [&](Request &request, Response &response){
                response << "Hello " << htmlEntities(request.get("name", "... what's your name ?")) << endl;
            });
        }
};


int main()
{
    MyController myController;
    Server server(8080);
    server.registerController(&myController);

    server.start(); 

    while (1) {
#ifdef WIN32
		Sleep(10000);
#else
        sleep(10);
#endif
    }
}
