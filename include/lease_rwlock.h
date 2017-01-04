#ifndef _LEASE_RWLOCK
#define _LEASE_RWLOCK
#include "rwlock.h"
class LeaseRWLock : public RWLock{
private:
    int sem;

public:
    LeaseRWLock();
    virtual ~LeaseRWLock();
    virtual void RLock();
    virtual void RUnlock();
    virtual void WLock();
    virtual void WUnlock();
};

#endif
