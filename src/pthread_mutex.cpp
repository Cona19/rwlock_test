#include "pthread_mutex.h"
#include <pthread.h>
#include <stdlib.h>

PthreadMutex::PthreadMutex() : RWLock(){
	pthread_mutex_init(&mutex, NULL);
}
PthreadMutex::~PthreadMutex(){
	pthread_mutex_destroy(&mutex);
}
data_t PthreadMutex::read(){
	data_t tmp;
	pthread_mutex_lock(&mutex);

	tmp = read_unsafe();

	pthread_mutex_unlock(&mutex);

	return tmp;
}
void PthreadMutex::write(data_t newval){
	pthread_mutex_lock(&mutex);
	write_unsafe(newval);
	pthread_mutex_unlock(&mutex);
}
