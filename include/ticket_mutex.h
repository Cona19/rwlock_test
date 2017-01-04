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
    virtual void RLock();
    virtual void RUnlock();
    virtual void WLock();
    virtual void WUnlock();
};

#endif
