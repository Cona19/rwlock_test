#ifndef _PTHREAD_RWLOCK
#define _PTHREAD_RWLOCK
#include <pthread.h>
#include "rwlock.h"
class PthreadRWLock : public RWLock{
private:
    pthread_rwlock_t rwlock;
public:
    PthreadRWLock();
    virtual ~PthreadRWLock();
    virtual void RLock();
    virtual void RUnlock();
    virtual void WLock();
    virtual void WUnlock();
};

#endif
