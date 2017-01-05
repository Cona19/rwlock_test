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
    virtual data_t read();
    virtual void write(data_t newval);
};

#endif
