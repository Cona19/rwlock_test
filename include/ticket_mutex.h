#ifndef _TICKET_MUTEX
#define _TICKET_MUTEX
#include "rwlock.h"
class TicketMutex : public RWLock{
private:
    int acquire_sem;
    int release_sem;
public:
    TicketMutex();
    virtual ~TicketMutex();
    virtual data_t read();
    virtual void write(data_t newval);
};

#endif
