#include <pthread.h>
#include <iostream>
#include <fstream>
#include <sched.h>
using namespace std;
#include "rwlock.h"
#include "no_rwlock.h"
#include "pthread_rwlock.h"
#include "pthread_mutex.h"
#include "simple_rwlock.h"
#include "boost_mutex.h"
#include "boost_rwlock.h"
#include "lease_rwlock.h"
#include "ticket_mutex.h"
#include "acc_timer.h"
#include "config.h"
#include "eval.h"

RWLock *shared_rec;
bool start_sign;

enum RWLockType{
    NO_RWLOCK = 0,
	TICKET_MUTEX,
	PTHREAD_RWLOCK,
	PTHREAD_MUTEX,
    SIMPLE_RWLOCK,
	BOOST_MUTEX,
	BOOST_RWLOCK,
    LEASE_RWLOCK,
    NUM_RWLOCK,
};
const char *lock_names[NUM_RWLOCK] = {
	"No RWLock",
	"Ticket RWLock",
	"Pthread RWLock",
	"Pthread Mutex",
	"Simple RWLock",
	"Boost Mutex",
	"Boost RWLock",
	"Lease RWLock",
};

void *rthdFunc(void *arg){
	unsigned long *res= (unsigned long*) arg;
    unsigned long val;
    int i;
    while(!start_sign) sched_yield();
    val = 0;
    for (i = 0; i < TASK_CNT; i++){
        val += shared_rec->read();
    }
    *res = val;
	return NULL;
}

void *wthdFunc(void *arg){
    int i;
    while(!start_sign) sched_yield();
    for (i = 0; i < TASK_CNT; i++){
        shared_rec->write(i);
	}
	return NULL;
}

RWLock *initRWLockByType(RWLockType type){
    switch(type){
    case NO_RWLOCK:
        return new NoRWLock();
    case PTHREAD_RWLOCK:
        return new PthreadRWLock();
    case PTHREAD_MUTEX:
        return new PthreadMutex();
    case BOOST_MUTEX:
        return new BoostMutex();
    case BOOST_RWLOCK:
        return new BoostRWLock();
    case SIMPLE_RWLOCK:
        return new SimpleRWLock();
    case LEASE_RWLOCK:
        return new LeaseRWLock();
    case TICKET_MUTEX:
        return new TicketMutex();
    default:
        return NULL;
    }
}

void initRWLock(RWLock **rec, RWLockType rwlock_type){
    data_t tmp = 0;
    ifstream fin;
    fin.open(FILE_PATH);
    if (fin.is_open()){
        fin>>tmp;
        fin.close();
    }
    else{
        cout<<FILE_PATH<<" not found"<<endl;
    }
	*rec = initRWLockByType(rwlock_type); 
    (*rec)->initialize(tmp, tmp);
}

void releaseRWLock(RWLock **rec){
	delete *rec;
	*rec = NULL;
}

acc_timer_t runCase(int num_rthd, int num_wthd){
	int i;
    unsigned long *r_result = new unsigned long[num_rthd];
    unsigned long *w_result = new unsigned long[num_wthd];
	unsigned long tot_r_result;
	pthread_t *rthd = new pthread_t[num_rthd];
	pthread_t *wthd = new pthread_t[num_wthd];
    acc_timer_t start_time, end_time, elapsed_time;
    start_sign = false;
	for (i = 0; i < num_rthd; i++){
        r_result[i] = 0;
		pthread_create(&rthd[i], NULL, rthdFunc, (void*)&r_result[i]);
    }
    for (i = 0; i < num_wthd; i++){
        w_result[i] = 0;
		pthread_create(&wthd[i], NULL, wthdFunc, (void*)&w_result[i]);
	}
    start_time = getTime();
    start_sign = true;
	tot_r_result = 0;
	for (i = 0; i < num_rthd; i++){
		if (pthread_join(rthd[i], NULL)){ 
			cout<<"pthread_join ERROR"<<endl;
        }
		tot_r_result += r_result[i];
	}
	for (i = 0; i < num_wthd; i++){
		if (pthread_join(wthd[i], NULL)){ 
			cout<<"pthread_join ERROR"<<endl;
        }
	}
    end_time = getTime();
    elapsed_time = end_time - start_time;

	cout<<tot_r_result<<endl;
	delete [] r_result;
	delete [] w_result;
	delete [] rthd;
	delete [] wthd;
	return elapsed_time;
}

void run(int num_rthd, int num_wthd){
    int rwlock_type;
	int i;
    acc_timer_t elapsed_time;
    double results[NUM_RWLOCK];
    for (rwlock_type = NO_RWLOCK; rwlock_type != NUM_RWLOCK; rwlock_type++){
        initRWLock(&shared_rec, (RWLockType)rwlock_type);
		elapsed_time = 0;
		for (i = 0; i < TEST_CNT; i++){
			elapsed_time += runCase(num_rthd, num_wthd);
		}
		cout<<"ENDENDEND"<<endl;
		results[rwlock_type] = elapsed_time/1000000.0/TEST_CNT;
		releaseRWLock(&shared_rec);
    }
    for (rwlock_type = NO_RWLOCK; rwlock_type != NUM_RWLOCK; rwlock_type++){
		cout<<lock_names[rwlock_type]<<" : "<<results[rwlock_type]<<"ms"<<endl;
	}
	cout<<"Run end"<<endl;
}
