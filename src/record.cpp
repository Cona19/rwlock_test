#include "record.h"
#include "rwlock.h"
#include "no_rwlock.h"
#include "pthread_rwlock.h"


void Record::write(data_t newval){
    rwlock->WLock();
    this->data = newval;
    rwlock->WUnlock();
}

data_t Record::read(){
    data_t data;
    rwlock->RLock();
    data = this->data;
    rwlock->RUnlock();
    return data;
}

void Record::setLock(RWLockType type){
    release();
    switch(type){
    case NO_RWLOCK:
        this->rwlock = new NoRWLock();
        break;
    case PTHREAD_RWLOCK:
        this->rwlock = new PthreadRWLock();
        break;
    //case SIMPLE_RWLOCK:
     //   this->rwlock = new NoRWLock();
      //  break;
    default:
        this->rwlock = NULL;
        break;
    }
}

void Record::release(){
    if (this->rwlock){
        delete this->rwlock;
        this->rwlock = NULL;
    }
}

Record::Record(){
    this->data = 0;
    this->rwlock = NULL;
}

Record::~Record(){
    release();
}

