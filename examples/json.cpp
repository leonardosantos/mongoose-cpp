#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <mongoose-cpp/Server.h>
#include <mongoose-cpp/JsonController.h>

using namespace std;
using namespace Mongoose;

class MyController : public JsonController
{
    public:
 
        void setup()
        {
            // Example of prefix, putting all the urls into "/api"
            setPrefix("/api");

            auto hello = [&](Request &request, Response &response){
                int i;

                for (i=0; i<12; i++) {
                    response["users"][i]["Name"] = "Bob";
                }

                response["timestamp"] = (int)time(NULL);
            };

            // Hello demo
            registerRoute("GET", "/", hello);
            registerRoute("GET", "/hello", hello);
        }
};

volatile static bool running = true;

void handle_signal(int sig)
{
    if (running) {
        cout << "Exiting..." << endl;
        running = false;
    }
}

int main()
{
    srand(time(NULL));

    signal(SIGINT, handle_signal);

    MyController myController;
    Server server(8080);
    server.registerController(&myController);
    server.setOption("enable_directory_listing", "false");
    server.start();

    cout << "Server started, routes:" << endl;
    myController.dumpRoutes();

    while (running) {
#ifdef WIN32
		Sleep(10000);
#else
        sleep(10);
#endif
    }

    server.stop();
    
    return EXIT_SUCCESS;
}
