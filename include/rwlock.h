#ifndef _RWLOCK
#define _RWLOCK
#include "record.h"

class RWLock{
private:
	Record rec;
protected:
	data_t read_unsafe();
    void write_unsafe(data_t newval);
public:
    RWLock();
    virtual ~RWLock();
    virtual data_t read();
    virtual void write(data_t newval);
	void initialize(data_t dat1, data_t dat2);
};

#endif
