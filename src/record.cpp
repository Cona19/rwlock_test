#include "record.h"
#include "rwlock.h"
#include "no_rwlock.h"
#include "pthread_rwlock.h"
#include "pthread_mutex.h"
#include "simple_rwlock.h"
#include "boost_mutex.h"

const char *lock_names[NUM_RWLOCK] = {
	"No RWLock",
	"Pthread RWLock",
	"Pthread Mutex",
	"Simple RWLock",
	"Boost Mutex"
};

void Record::initialize(data_t dat1, data_t dat2){
    this->dat1 = dat1;
    this->dat2 = dat2;
}

void Record::write(data_t newval){
	data_t tmp;
    rwlock->WLock();
	tmp = this->dat1 + newval;
	this->dat1 = this->dat2 - newval;
    this->dat2 = tmp;
    rwlock->WUnlock();
}

data_t Record::read(){
    data_t data;
    rwlock->RLock();
    data = dat1 + dat2;
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
    case PTHREAD_MUTEX:
        this->rwlock = new PthreadMutex();
        break;
    case BOOST_MUTEX:
        this->rwlock = new BoostMutex();
        break;
    case SIMPLE_RWLOCK:
        this->rwlock = new SimpleRWLock();
        break;
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
    this->dat1 = this->dat2 = 0;
    this->rwlock = NULL;
}

Record::~Record(){
    release();
}

