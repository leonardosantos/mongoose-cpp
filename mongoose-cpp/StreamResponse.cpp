#include <sstream>
#include <mongoose-cpp/StreamResponse.h>

using namespace std;

namespace Mongoose {
string StreamResponse::getBody() { return this->str(); }
};
