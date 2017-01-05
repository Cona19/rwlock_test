#include "lease_rwlock.h"
#include <pthread.h>
#define YIELD_WAIT

#ifdef YIELD_WAIT
#define yield() pthread_yield()
#else
#define yield() 
#endif

LeaseRWLock::LeaseRWLock() : RWLock(){
}
LeaseRWLock::~LeaseRWLock(){
}
data_t LeaseRWLock::read(){
	data_t tmp;
	tmp = read_unsafe();
	return tmp;
}
void LeaseRWLock::write(data_t newval){
	write_unsafe(newval);
}
