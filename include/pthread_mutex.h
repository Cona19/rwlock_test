#ifndef _PTHREAD_MUTEX
#define _PTHREAD_MUTEX
#include <pthread.h>
#include "rwlock.h"
class PthreadMutex : public RWLock{
private:
    pthread_mutex_t mutex;
public:
    PthreadMutex();
    virtual ~PthreadMutex();
    virtual void RLock();
    virtual void RUnlock();
    virtual void WLock();
    virtual void WUnlock();
};

#endif
