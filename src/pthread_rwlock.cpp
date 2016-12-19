#include "pthread_rwlock.h"
#include <pthread.h>

PthreadRWLock::PthreadRWLock() : RWLock(){
    pthread_rwlock_init(&rwlock, NULL);
}
PthreadRWLock::~PthreadRWLock(){
    pthread_rwlock_destroy(&rwlock);
}
void PthreadRWLock::RLock(){
}
void PthreadRWLock::RUnlock(){
}
void PthreadRWLock::WLock(){
}
void PthreadRWLock::WUnlock(){
}
