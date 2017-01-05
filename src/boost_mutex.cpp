#include "boost_mutex.h"

BoostMutex::BoostMutex() : RWLock(){
}
BoostMutex::~BoostMutex(){
}
data_t BoostMutex::read(){
	data_t tmp;
	mutex.lock();
	tmp = read_unsafe();
	mutex.unlock();
	return tmp;
}
void BoostMutex::write(data_t newval){
	mutex.lock();
	write_unsafe(newval);
	mutex.unlock();
}
