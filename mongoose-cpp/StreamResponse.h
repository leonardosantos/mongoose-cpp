#ifndef _MONGOOSE_CPP_STREAM_RESPONSE_H
#define _MONGOOSE_CPP_STREAM_RESPONSE_H

#include <map>
#include <sstream>
#include <iostream>

#include <mongoose-cpp/Response.h>

using namespace std;

/**
 * A stream response to a request
 */
namespace Mongoose
{
    class MONGOOSE_CPP_EXPORT StreamResponse : public ostringstream, public Response
    {
        public:
            /**
             * Gets the response body
             *
             * @return string the response body
             */
            virtual string getBody();
    };
}

#endif
