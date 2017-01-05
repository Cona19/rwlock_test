#include "simple_rwlock.h"
#include <pthread.h>
#define YIELD_WAIT

#ifdef YIELD_WAIT
#define yield() pthread_yield()
#else
#define yield() 
#endif

SimpleRWLock::SimpleRWLock() : RWLock(){
	sem = 0;
}
SimpleRWLock::~SimpleRWLock(){
}
data_t SimpleRWLock::read(){
	data_t tmp;

	//Acquire reader lock
	while(1){
		while(this->sem < 0)
			yield();
		if (__sync_fetch_and_add(&sem, 1) >= 0)
			break;
	}

	tmp = read_unsafe();

	//Release reader lock
	__sync_fetch_and_sub(&sem, 1);

	return tmp;
}
void SimpleRWLock::write(data_t newval){
	//Acquire writer lock
	while(!__sync_bool_compare_and_swap(&sem, 0, -10000))
		yield();

	write_unsafe(newval);

	//Release writer lock
	sem = 0;
}
