#ifndef _NO_RWLOCK
#define _NO_RWLOCK
#include "rwlock.h"
class NoRWLock : public RWLock{
private:
public:
    NoRWLock();
    virtual ~NoRWLock();
    virtual data_t read();
    virtual void write(data_t newval);
};

#endif
