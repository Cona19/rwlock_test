#include "boost_mutex.h"

BoostMutex::BoostMutex() : RWLock(){
}
BoostMutex::~BoostMutex(){
}
void BoostMutex::RLock(){
	mutex.lock();
}
void BoostMutex::RUnlock(){
	mutex.unlock();
}
void BoostMutex::WLock(){
	mutex.lock();
}
void BoostMutex::WUnlock(){
	mutex.unlock();
}
