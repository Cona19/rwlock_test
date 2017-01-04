#ifndef _BOOST_RWLOCK
#define _BOOST_RWLOCK
#include <boost/thread.hpp>
#include "rwlock.h"
class BoostRWLock : public RWLock{
private:
	boost::shared_mutex mutex;
public:
    BoostRWLock();
    virtual ~BoostRWLock();
    virtual void RLock();
    virtual void RUnlock();
    virtual void WLock();
    virtual void WUnlock();
};

#endif
