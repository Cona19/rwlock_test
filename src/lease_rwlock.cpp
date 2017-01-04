#include "lease_rwlock.h"
#include <pthread.h>
#define YIELD_WAIT

#ifdef YIELD_WAIT
#define yield() pthread_yield()
#else
#define yield() 
#endif

LeaseRWLock::LeaseRWLock() : RWLock(){
	sem = 0;
}
LeaseRWLock::~LeaseRWLock(){
}
void LeaseRWLock::RLock(){
	while(1){
		while(this->sem < 0)
			yield();
		if (__sync_fetch_and_add(&sem, 1) >= 0)
			break;
	}
}
void LeaseRWLock::RUnlock(){
	__sync_fetch_and_sub(&sem, 1);
}
void LeaseRWLock::WLock(){
	while(!__sync_bool_compare_and_swap(&sem, 0, -10000))
		yield();
}
void LeaseRWLock::WUnlock(){
	sem = 0;
}
