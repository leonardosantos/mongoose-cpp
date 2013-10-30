#ifndef _MONGOOSE_REQUEST_H
#define _MONGOOSE_REQUEST_H

#include <iostream>
#include <sstream>
#include <vector>
#ifdef ENABLE_REGEX_URL
    #include <regex>
#endif
#ifdef HAS_JSONCPP
    #include <json/json.h>
#endif
#include <mongoose.h>
#include "UploadFile.h"
#include "Response.h"

using namespace std;

/**
 * Request is a wrapper for the clients requests
 */
namespace Mongoose
{
    class Request
    {
        public:
            Request(struct mg_connection *connection);

            /**
             * Sends a given response to the client
             *
             * @param Response a response for this request
             */
            void writeResponse(Response *response);

            /**
             * Check if the variable given by key is present in GET or POST data
             *
             * @param string the name of the variable
             *
             * @return bool true if the param is present, false else
             */
            bool hasVariable(string key);

            /**
             * Get the value for a certain variable
             *
             * @param string the name of the variable
             * @param string the fallback value if the variable doesn't exists
             *
             * @return string the value of the variable if it exists, fallback else
             */
            string get(string key, string fallback = "");

#ifdef HAS_JSONCPP
            /**
             * Get the payload data as json
             *
             * @return the Json::Value of the payload data
             */
            Json::Value json_data();
#endif
            /**
             * Checks if the given cookie exists
             *
             * @param string the name of the cookie
             *
             * @return bool true if the given cookie is set
             */
            bool hasCookie(string key);

            /**
             * Try to get the cookie value
             *
             * @param string the name of the cookie
             * @param string the fallback value
             *
             * @retun the value of the cookie if it exists, fallback else
             */
            string getCookie(string key, string fallback = "");

            /**
             * Handle uploads to the target directory
             *
             * @param string the target directory
             */
            void upload(string targetDirectory);

            string getUrl();
            string getMethod();
#ifdef ENABLE_REGEX_URL
            smatch getMatches();
            bool match(string pattern);
#endif
            bool readVariable(const char *data, string key, string &output);

            /**
             * Files uploaded in this request
             */
            vector<UploadFile> uploadFiles;

        protected:
            string data;
            string method;
            string url;
#ifdef ENABLE_REGEX_URL
            string key;
            smatch matches;
#endif
            struct mg_connection *connection;
            struct mg_request_info *request;
    };
};

#endif
