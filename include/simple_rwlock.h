#ifndef _SIMPLE_RWLOCK
#define _SIMPLE_RWLOCK
#include "rwlock.h"
class SimpleRWLock : public RWLock{
private:
    int sem;

public:
    SimpleRWLock();
    virtual ~SimpleRWLock();
    virtual void RLock();
    virtual void RUnlock();
    virtual void WLock();
    virtual void WUnlock();
};

#endif
