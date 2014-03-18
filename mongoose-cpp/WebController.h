#ifndef _MONGOOSE_CPP_WEB_CONTROLLER_H
#define _MONGOOSE_CPP_WEB_CONTROLLER_H

#include <mongoose-cpp/Request.h>
#include <mongoose-cpp/Response.h>
#include <mongoose-cpp/Controller.h>
#include <mongoose-cpp/Sessions.h>
#include <mongoose-cpp/Mutex.h>
#include <mongoose-cpp/StreamResponse.h>
#include <mongoose-cpp/Utils.h>

using namespace std;

/**
 * A web controller is a controller that serves HTML pages and has sessions
 */
namespace Mongoose {
class MONGOOSE_CPP_EXPORT WebController : public Controller, public Utils {
   public:
    /**
     * Creates a web controller, each gcDivisor request, the sessions will be
     * garbage collected
     */
    WebController(int gcDivisor = 100);

    /**
     * Gets the session for a request/response
     *
     * @param Request the request
     * @param Response the response
     *
     * @return Session the session for the request/response
     */
    Session &getSession(Request &request, Response &response);

    /**
     * Pre process the request, this will set the content type to text/html
     * and ping the user session
     *
     * @param Request the request
     * @param Response the response
     */
    void preProcess(Request &request, Response &response);

   protected:
    Sessions sessions;
    int gcDivisor;
    int counter;
    Mutex mutex;
};
}

#endif
