#ifndef _SIMPLE_RWLOCK
#define _SIMPLE_RWLOCK
#include "rwlock.h"
class SimpleRWLock : public RWLock{
private:
    int sem;
public:
    SimpleRWLock();
    virtual ~SimpleRWLock();
    virtual data_t read();
    virtual void write(data_t newval);
};

#endif
