#ifndef _MONGOOSE_CPP_RESPONSE_H
#define _MONGOOSE_CPP_RESPONSE_H

#include <map>
#include <sstream>
#include <iostream>
#if HAS_JSONCPP
#include <json/json.h>
#endif

#include <mongoose-cpp/Common.h>

/**
 * A response to a request
 */
namespace Mongoose {
using namespace std;
class MONGOOSE_CPP_EXPORT Response :
#if HAS_JSONCPP
    public Json::Value,
#endif
    public ostringstream {
   public:
    Response();
    ~Response();

    /**
     * Test if the given header is present
     *
     * @param string the header key
     *
     * @return bool true if the header is set
     */
    bool hasHeader(string key);

    /**
     * Sets the header
     *
     * @param key the header key
     *
     * @param value the header value
     */
    void setHeader(string key, string value);

    /**
     * Get the data of the response, this will contain headers and
     * body
     *
     * @return string the response data
     */
    string getData();

    /**
     * Gets the response body
     *
     * @return string the response body
     */
    string getBody();

    /**
     * Sets the cookie, note that you can only define one cookie by request
     * for now
     *
     * @param string the key of the cookie
     * @param string value the cookie value
     */
    void setCookie(string key, string value);

    /**
     * Sets the response code
     */
    void setCode(int code);

    /**
     * Sets the human readability of the response
     *
     * @param bool true for human readable
     */
    void setHuman(bool human);

   protected:
    int code;
    map<string, string> headers;
    bool humanReadable;
};
}

#endif
