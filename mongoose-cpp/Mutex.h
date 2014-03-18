#ifndef _MONGOOSE_CPP_MUTEX_H
#define _MONGOOSE_CPP_MUTEX_H

#ifndef _MSC_VER
#include <pthread.h>
#else
#include <windows.h>
typedef HANDLE pthread_mutex_t;
#endif

#include <mongoose-cpp/Common.h>

/**
 * A mutex allow thread-safe operations
 */
namespace Mongoose {
class MONGOOSE_CPP_EXPORT Mutex {
   public:
    Mutex();
    virtual ~Mutex();

    /**
     * Locks the mutex
     */
    virtual void lock();

    /**
     * Unlock the mutex
     */
    virtual void unlock();

   protected:
    pthread_mutex_t _mutex;
};
}

#endif
