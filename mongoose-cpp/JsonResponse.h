#ifndef _MONGOOSE_CPP_JSON_RESPONSE_H
#define _MONGOOSE_CPP_JSON_RESPONSE_H

#include <map>
#include <sstream>
#include <iostream>
#include <json/json.h>

#include <mongoose-cpp/Response.h>

using namespace std;

/**
 * A stream response to a request
 */
namespace Mongoose
{
    class MONGOOSE_CPP_EXPORT JsonResponse : public Json::Value, public Response
    {
        public:
            JsonResponse();

            /**
             * Gets the response body
             *
             * @return string the response body
             */
            virtual string getBody();

            /**
             * Sets the human readability of the response
             *
             * @param bool true for human readable
             */
            void setHuman(bool human);

        protected:
            bool humanReadable;
    };
}

#endif
