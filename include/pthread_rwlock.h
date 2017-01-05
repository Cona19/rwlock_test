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
    virtual data_t read();
    virtual void write(data_t newval);
};

#endif
