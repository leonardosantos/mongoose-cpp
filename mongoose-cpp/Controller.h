#ifndef _MONGOOSE_CPP_CONTROLLER_H
#define _MONGOOSE_CPP_CONTROLLER_H

#include <map>
#include <functional>
#include <iostream>
#include <mongoose-cpp/Common.h>
#include <mongoose-cpp/Request.h>
#include <mongoose-cpp/Response.h>
#include <mongoose-cpp/WebSocket.h>

/**
 * A controller is a module that respond to requests
 *
 * You can override the preProcess, process and postProcess to answer to
 * the requests
 */
namespace Mongoose {

typedef std::function<void(Request& request, Response& response)> Callback;

class Server;

class MONGOOSE_CPP_EXPORT Controller {
   public:
    Controller();
    virtual ~Controller();

    /**
     * Sets the reference to the server hosting this controller
     *
     * @param Server the hosting server
     */
    virtual void setServer(Server *server);

    /**
     * Called before a request is processed
     *
     * @param Request the request
     * @param Response the response
     */
    virtual void preProcess(Request &request, Response &response);

    /**
     * Called to process a request
     *
     * @param Request the request
     *
     * @return Response the created response, or NULL if the controller
     *         does not handle this request
     */
    virtual Response *process(Request &request);

    /**
     * Called after a request is processed, if the controller responded
     *
     * @param Request the request
     * @param Response the response
     */
    virtual void postProcess(Request &request, Response &response);

    /**
     * Handle a request, this will try to match the request, if this
     * controller handles it, it will preProcess, process then postProcess it
     *
     * @param Request the request
     *
     * @return Response the created response, or NULL if the controller
     *         does not handle this request
     */
    virtual Response *handleRequest(Request &request);

    /**
     * Sets the controller prefix, for instance "/api"
     *
     * @param string the prefix of all urls for this controller
     */
    void setPrefix(string prefix);

    /**
     * Called when a new websocket connection is ready
     *
     * @param WebSocket the instance of the connection
     */
    virtual void webSocketReady(WebSocket *websocket);

    /**
     * Called when data arrive in a websocket connection
     *
     * @param WebSocket the instance of the connection
     * @param string the data arriving
     */
    virtual void webSocketData(WebSocket *websocket, string data);

    /**
     * Registers a route to the controller
     *
     * @param string the route path
     * @param RequestHandlerBase the request handler for this route
     */
    virtual void registerRoute(string httpMethod, string route, Callback callback);

    /**
     * Initializes the route and settings
     */
    virtual void setup();

    /**
     * Dump all routes
     */
    void dumpRoutes();

    /**
     * Called when an exception occur during the rendering
     *
     * @param string the error message
     *
     * @return response a response to send, 404 will occur if NULL
     */
    virtual Response *serverInternalError(string message);

    /**
     * Checks if the method/url pair is handles by the controller
     *
     * @param method HTTP
     * @param url of the request
     *
     * @return a bool indicating wether the controller handles the given method and url or not
     */
    bool handles(string method, string url);

    /**
     * Accessor for the url list.
     *
     * @return a list of the accepted urls
     */
    vector<string> getUrls();

   protected:
    Server *server;
    string prefix;
    map<string, Callback> routes;
    vector<string> urls;
     
    /**
     * Gets the appropriate callback for the request
     *
     * @param method HTTP
     * @param url of the request
     *
     * @return the corresponding callback
     */
    Callback resolve(string method, string url);

};

}  // namespace Mongoose

#endif
