#include "ticket_mutex.h"
#include <pthread.h>
#define YIELD_WAIT

#ifdef YIELD_WAIT
#define yield() pthread_yield()
#else
#define yield() 
#endif

TicketMutex::TicketMutex() : RWLock(){
	acquire_sem = 0;
	release_sem = 0;
}
TicketMutex::~TicketMutex(){
}
data_t TicketMutex::read(){
	data_t tmp;
	int my_sem;
	//Acquire mutex
	my_sem = __sync_fetch_and_add(&acquire_sem, 1);
	while(my_sem != release_sem){
		yield();
	}

	tmp = read_unsafe();

	//Release mutex
	release_sem++;
	return tmp;
}
void TicketMutex::write(data_t newval){
	int my_sem;
	//Acquire mutex
	my_sem = __sync_fetch_and_add(&acquire_sem, 1);
	while(my_sem != release_sem){
		yield();
	}

	write_unsafe(newval);

	//Release mutex
	release_sem++;
}
