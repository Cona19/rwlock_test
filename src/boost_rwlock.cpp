#include "boost_rwlock.h"

BoostRWLock::BoostRWLock() : RWLock(){
}
BoostRWLock::~BoostRWLock(){
}
void BoostRWLock::RLock(){
	mutex.lock_shared();
}
void BoostRWLock::RUnlock(){
	mutex.unlock_shared();
}
void BoostRWLock::WLock(){
	mutex.lock();
}
void BoostRWLock::WUnlock(){
	mutex.unlock();
}
