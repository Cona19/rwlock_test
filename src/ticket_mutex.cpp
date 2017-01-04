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
void TicketMutex::RLock(){
	int my_sem;
	my_sem = __sync_fetch_and_add(&acquire_sem, 1);
	while(my_sem != release_sem){
		yield();
	}
}
void TicketMutex::RUnlock(){
	release_sem++;
}
void TicketMutex::WLock(){
	int my_sem;
	my_sem = __sync_fetch_and_add(&acquire_sem, 1);
	while(my_sem != release_sem){
		yield();
	}
}
void TicketMutex::WUnlock(){
	release_sem++;
}
