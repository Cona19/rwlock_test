#include "pthread_mutex.h"
#include <pthread.h>
#include <stdlib.h>

PthreadMutex::PthreadMutex() : RWLock(){
	pthread_mutex_init(&mutex, NULL);
}
PthreadMutex::~PthreadMutex(){
	pthread_mutex_destroy(&mutex);
}
void PthreadMutex::RLock(){
	pthread_mutex_lock(&mutex);
}
void PthreadMutex::RUnlock(){
	pthread_mutex_unlock(&mutex);
}
void PthreadMutex::WLock(){
	pthread_mutex_lock(&mutex);
}
void PthreadMutex::WUnlock(){
	pthread_mutex_unlock(&mutex);
}
