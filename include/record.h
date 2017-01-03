#ifndef _RECORD
#define _RECORD
#include "rwlock.h"

typedef unsigned long data_t;
enum RWLockType{
    NO_RWLOCK = 0,
    PTHREAD_RWLOCK,
    SIMPLE_RWLOCK,
    NUM_RWLOCK
};

class Record{
private:
    data_t dat1;
    data_t dat2;
    RWLock *rwlock;
public:
    Record();
    ~Record();
    void write(data_t newval);
    data_t read();
    void setLock(RWLockType type);
    void initialize(data_t dat1, data_t dat2);
    void release();
};
#endif
