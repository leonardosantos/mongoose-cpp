#ifndef _MONGOOSE_CPP_UTILS_H
#define _MONGOOSE_CPP_UTILS_H

#include <iostream>
#include <mongoose-cpp/Common.h>

using namespace std;

namespace Mongoose {
class MONGOOSE_CPP_EXPORT Utils {
   public:
    string htmlEntities(string data);
};
}

#endif
