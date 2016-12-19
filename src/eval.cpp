#include <pthread.h>
#include <iostream>
#include <fstream>
#include <sched.h>
using namespace std;
#include "record.h"
#include "acc_timer.h"
#include "config.h"
#include "eval.h"

Record rec;
bool start_sign;

void *rthdFunc(void *arg){
	unsigned long tid = *((unsigned long*) arg);
    unsigned long val;
    int i;
    while(!start_sign) sched_yield();
    val = 0;
    for (i = 0; i < TASK_CNT; i++){
        val += rec.read();
    }
    //printf("%lu = %lu\n",tid, val);
	return NULL;
}

void *wthdFunc(void *arg){
	unsigned long tid = *((unsigned long*) arg);
    int i;
    while(!start_sign) sched_yield();
    for (i = 0; i < TASK_CNT; i++){
        rec.write(i); }
    //printf("%lu\n",tid);
	return NULL;
}

void initRecord(Record *rec, RWLockType rwlock_type){
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
    rec->setLock(rwlock_type);
    rec->write(tmp);
}

void runCase(){
	int i;
    unsigned long rtid[RTHD_NUM];
    unsigned long wtid[WTHD_NUM];
	pthread_t rthd[RTHD_NUM];
	pthread_t wthd[WTHD_NUM];
    acc_timer_t start_time, end_time, elapsed_time;
    start_sign = false;
	for (i = 0; i < RTHD_NUM; i++){
        rtid[i] = i+1;
		pthread_create(&rthd[i], NULL, rthdFunc, (void*)&rtid[i]);
    }
    for (i = 0; i < WTHD_NUM; i++){
        wtid[i] = i+1;
		pthread_create(&wthd[i], NULL, wthdFunc, (void*)&wtid[i]);
	}
    start_time = getTime();
    start_sign = true;
	for (i = 0; i < RTHD_NUM; i++){
		if (pthread_join(rthd[i], NULL)){ 
			printf("pthread_join ERROR\n");
        }
	}
    end_time = getTime();
    elapsed_time = end_time - start_time;

    cout<<elapsed_time/1000000.0<<"ms"<<endl;
}

void run(){
    int rwlock_type;

    for (rwlock_type = NO_RWLOCK; rwlock_type != NUM_RWLOCK; rwlock_type++){
        initRecord(&rec, (RWLockType)rwlock_type);
        runCase();
    }
}
