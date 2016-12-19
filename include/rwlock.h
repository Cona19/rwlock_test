#ifndef _RWLOCK
#define _RWLOCK
class RWLock{
private:
public:
    RWLock();
    virtual ~RWLock();
    virtual void RLock();
    virtual void RUnlock();
    virtual void WLock();
    virtual void WUnlock();
};

#endif
