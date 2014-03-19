#ifndef _MSC_VER
#include <unistd.h>
#include <stdlib.h>
#else
#include <time.h>
#endif
#include <signal.h>
#include <mongoose-cpp/Server.h>
#include <mongoose-cpp/WebController.h>

using namespace std;
using namespace Mongoose;

class MyController : public WebController
{
    public: 

        void forbid(Request &request, Response &response){
            response.setCode(Response::codes::FORBIDDEN);
            response << "403 forbidden demo";
        }

        void setup()
        {

            auto hello = [&](Request &request, Response &response){
                response << "Hello " << htmlEntities(request.get("name", "... what's your name ?")) << endl;
            };

            // Hello demo
            route("GET", "/hello", hello);
            route("GET", "/", hello);
            
            // Form demo
            route("GET", "/form", [&](Request &request, Response &response){
                response << "<form method=\"post\">" << endl;
                response << "<input type=\"text\" name=\"test\" /><br >" << endl;
                response << "<input type=\"submit\" value=\"Envoyer\" />" << endl;
                response << "</form>" << endl;
            });

            route("POST", "/form", [&](Request &request, Response &response){
                response << "Test=" << htmlEntities(request.get("test", "(unknown)"));
            });

            // Session demo
            route("GET", "/session", [&](Request &request, Response &response){
                Session &session = getSession(request, response);

                if (session.hasValue("try")) {
                    response << "Session value: " << session.get("try");
                } else {
                    ostringstream val;
                    val << time(NULL);
                    session.setValue("try", val.str());
                    response << "Session value set to: " << session.get("try");
                }
            });

            // Exception example
            route("GET", "/exception", [&](Request &request, Response &response){
                throw string("Exception example");
            });

            // 403 demo
            route("GET", "/403", std::bind(&MyController::forbid, this, std::placeholders::_1, std::placeholders::_2));

            // File upload demo
            route("GET", "/upload", [&](Request &request, Response &response){
                response << "<h1>File upload demo (don't forget to create a tmp/ directory)</h1>";
                response << "<form enctype=\"multipart/form-data\" method=\"post\">";
                response << "Choose a file to upload: <input name=\"file\" type=\"file\" /><br />";
                response << "<input type=\"submit\" value=\"Upload File\" />";
                response << "</form>";
            });
            route("POST", "/upload", [&](Request &request, Response &response){
                request.handleUploads();

                // Iterate through all the uploaded files
                vector<UploadFile>::iterator it = request.uploadFiles.begin();
                for (; it != request.uploadFiles.end(); it++) {
                    UploadFile file = *it;
                    file.saveTo("tmp/");
                    response << "Uploaded file: " << file.getName() << endl;
                }
            });
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
    int t;
#ifdef _MSC_VER
    time_t ltime;
    time(&ltime);
    t = ltime;
#else
    t = time(NULL);
#endif
    srand(t);

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
        Sleep(1000);
#else
        sleep(1);
#endif
    }

    server.stop();
    
    return EXIT_SUCCESS;
}
