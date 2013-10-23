#include <mongoose-cpp/UploadFile.h>

namespace Mongoose
{
    UploadFile::UploadFile(string filename_)
        : filename(filename_)
    {
    }

    string UploadFile::getName()
    {
        return filename;
    }
}
