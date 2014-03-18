#ifndef _MONGOOSE_CPP_JSON_CONTROLLER_H
#define _MONGOOSE_CPP_JSON_CONTROLLER_H

#include <mongoose-cpp/Request.h>
#include <mongoose-cpp/Response.h>
#include <mongoose-cpp/WebController.h>
#include <mongoose-cpp/JsonResponse.h>

using namespace std;

/**
 * A json controller is a controller that serves JSON API
 */
namespace Mongoose {
class MONGOOSE_CPP_EXPORT JsonController : public WebController {
   public:
    /**
     * Creates a json controller, each gcDivisor request, the sessions will be
     * garbage collected
     */
    JsonController(int gcDivisor = 100);

    /**
     * Pre process the request, this will set the content type to text/html
     * and ping the user session
     *
     * @param Request the request
     * @param Response the response
     */
    void preProcess(Request &request, Response &response);
};
}

#endif
