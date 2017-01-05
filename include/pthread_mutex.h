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
    virtual data_t read();
    virtual void write(data_t newval);
};

#endif
