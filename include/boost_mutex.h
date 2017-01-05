#ifndef _BOOST_MUTEX
#define _BOOST_MUTEX
#include <boost/thread.hpp>
#include "rwlock.h"
class BoostMutex : public RWLock{
private:
	boost::mutex mutex;
public:
    BoostMutex();
    virtual ~BoostMutex();
    virtual data_t read();
    virtual void write(data_t newval);
};

#endif
