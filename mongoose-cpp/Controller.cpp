#include <iostream>
#include <regex>
#include <mongoose-cpp/Controller.h>
#include <mongoose-cpp/Response.h>

using namespace std;

namespace Mongoose {
Controller::Controller() : prefix(""), server(NULL) {}

void Controller::setup() {}

void Controller::setServer(Server *server_) { server = server_; }

void Controller::webSocketReady(WebSocket *websocket) {}

void Controller::webSocketData(WebSocket *websocket, string data) {}

Controller::~Controller() { routes.clear(); }

Callback Controller::resolve(string method, string url) {
    if (url.back() == '/')
        url.pop_back();
    string key = method + ":" + url;
    smatch matches;
    for (auto it = routes.begin(); it != routes.end(); it++)
        if (regex_match(key, matches, regex(it->first)))
            return it->second;
    throw UnknownRequest();
}

bool Controller::handles(string method, string url) {
    try {
        resolve(method, url);
        return true;
    }
    catch (UnknownRequest) {
        return false;
    }
}

Response *Controller::process(Request &request) {
    Response *response = new Response();
    for (auto it = routes.begin(); it != routes.end(); it++)
        if (request.match(it->first)) {
            preProcess(request, *response);
            it->second(request, *response);
            break;
        }
    return response;
}

void Controller::preProcess(Request &request, Response &response) {}

void Controller::postProcess(Request &request, Response &response) {}

Response *Controller::handleRequest(Request &request) {
    Response *response = process(request);

    if (response != NULL)
        postProcess(request, *response);

    return response;
}

void Controller::setPrefix(string prefix_) { prefix = prefix_; }

Callback Controller::route(string httpMethod, string url, Callback callback) {
    string key = httpMethod + ":" + prefix + url + "/?";
    routes[key] = callback;
    urls.push_back(prefix + url);
    return callback;
}

void Controller::dumpRoutes() {
    for (auto it = routes.begin(); it != routes.end(); it++)
        cout << (*it).first << endl;
}

Response *Controller::serverInternalError(string message) {
    Response *response = new Response;

    response->setCode(Response::codes::SERVER_ERROR);
    *response << "500 Server internal error: " << message;

    return response;
}

vector<string> Controller::getUrls() { return urls; }
};
