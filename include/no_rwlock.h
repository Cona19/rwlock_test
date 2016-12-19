#ifndef _NO_RWLOCK
#define _NO_RWLOCK
#include "rwlock.h"
class NoRWLock : public RWLock{
private:
public:
    NoRWLock();
    virtual ~NoRWLock();
    virtual void RLock();
    virtual void RUnlock();
    virtual void WLock();
    virtual void WUnlock();
};

#endif
