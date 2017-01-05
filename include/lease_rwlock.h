#ifndef _LEASE_RWLOCK
#define _LEASE_RWLOCK
#include "rwlock.h"
class LeaseRWLock : public RWLock{
private:
public:
    LeaseRWLock();
    virtual ~LeaseRWLock();
    virtual data_t read();
    virtual void write(data_t newval);
};

#endif
