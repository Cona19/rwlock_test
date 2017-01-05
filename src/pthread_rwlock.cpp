#include "pthread_rwlock.h"
#include <pthread.h>

PthreadRWLock::PthreadRWLock() : RWLock(){
    pthread_rwlock_init(&rwlock, NULL);
}
PthreadRWLock::~PthreadRWLock(){
	pthread_rwlock_destroy(&rwlock);
}
data_t PthreadRWLock::read(){
	data_t tmp;
	pthread_rwlock_rdlock(&rwlock);
	tmp = read_unsafe();
	pthread_rwlock_unlock(&rwlock);
	return tmp;
}
void PthreadRWLock::write(data_t newval){
	pthread_rwlock_wrlock(&rwlock);
	write_unsafe(newval);
	pthread_rwlock_unlock(&rwlock);
}
