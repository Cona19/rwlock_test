#include "boost_rwlock.h"

BoostRWLock::BoostRWLock() : RWLock(){
}
BoostRWLock::~BoostRWLock(){
}
data_t BoostRWLock::read(){
	boost::shared_lock<boost::shared_mutex> lock(mutex);
	return read_unsafe();
}
void BoostRWLock::write(data_t newval){
	boost::upgrade_lock<boost::shared_mutex> lock(mutex);
	boost::upgrade_to_unique_lock<boost::shared_mutex> unique_lock(lock);
	write_unsafe(newval);
}
