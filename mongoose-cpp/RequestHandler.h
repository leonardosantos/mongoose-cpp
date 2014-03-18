#ifndef _MONGOOSE_CPP_REQUEST_HANDLER_H
#define _MONGOOSE_CPP_REQUEST_HANDLER_H

#include <mongoose-cpp/Request.h>
#include <mongoose-cpp/Response.h>
#include <string>

namespace Mongoose {
class MONGOOSE_CPP_EXPORT RequestHandlerBase {
   public:
    virtual Response *process(Request &request) = 0;
};

template <typename T>
class RequestHandler : public RequestHandlerBase {
   public:
    typedef void (T::*fPtr)(Request &request, Response &response);

    RequestHandler(T *controller_, fPtr function_) : controller(controller_), function(function_) {}

    Response *process(Request &request) {
        Response *response = new Response;

        try {
            controller->preProcess(request, *response);
            (controller->*function)(request, *response);
        }
        catch (string exception) {
            return controller->serverInternalError(exception);
        }
        catch (const std::exception &e) {
            return controller->serverInternalError(e.what());
        }
        catch (...) {
            return controller->serverInternalError("Unknown error");
        }

        return response;
    }

   protected:
    T *controller;
    fPtr function;
};
}

#endif
