#include "pthread_rwlock.h"
#include <pthread.h>

PthreadRWLock::PthreadRWLock() : RWLock(){
    pthread_rwlock_init(&rwlock, NULL);
}
PthreadRWLock::~PthreadRWLock(){
	pthread_rwlock_destroy(&rwlock);
}
void PthreadRWLock::RLock(){
	pthread_rwlock_rdlock(&rwlock);
}
void PthreadRWLock::RUnlock(){
	pthread_rwlock_unlock(&rwlock);
}
void PthreadRWLock::WLock(){
	pthread_rwlock_wrlock(&rwlock);
}
void PthreadRWLock::WUnlock(){
	pthread_rwlock_unlock(&rwlock);
}
