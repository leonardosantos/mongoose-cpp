#ifndef _MONGOOSE_CPP_UPLOAD_FILE_H
#define _MONGOOSE_CPP_UPLOAD_FILE_H

#include <string>
#include <mongoose-cpp/Common.h>

using namespace std;

/**
 * A file uploaded in a request
 */
namespace Mongoose
{
    class MONGOOSE_CPP_EXPORT UploadFile
    {
        public:
            UploadFile(string filename);

            string getName();

        protected:
            string filename;
    };
};

#endif // _MONGOOSE_CPP_UPLOAD_FILE_H
