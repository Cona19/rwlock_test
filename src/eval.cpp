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
	unsigned long *res= (unsigned long*) arg;
    unsigned long val;
    int i;
    while(!start_sign) sched_yield();
    val = 0;
    for (i = 0; i < TASK_CNT; i++){
        val += rec.read();
    }
    *res = val;
	return NULL;
}

void *wthdFunc(void *arg){
    int i;
    while(!start_sign) sched_yield();
    for (i = 0; i < TASK_CNT; i++){
        rec.write(i);
	}
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
    rec->initialize(tmp, tmp);
}

acc_timer_t runCase(){
	int i;
    unsigned long r_result[RTHD_NUM];
    unsigned long w_result[WTHD_NUM];
	unsigned long tot_r_result;
	pthread_t rthd[RTHD_NUM];
	pthread_t wthd[WTHD_NUM];
    acc_timer_t start_time, end_time, elapsed_time;
    start_sign = false;
	for (i = 0; i < RTHD_NUM; i++){
        r_result[i] = 0;
		pthread_create(&rthd[i], NULL, rthdFunc, (void*)&r_result[i]);
    }
    for (i = 0; i < WTHD_NUM; i++){
        w_result[i] = 0;
		pthread_create(&wthd[i], NULL, wthdFunc, (void*)&w_result[i]);
	}
    start_time = getTime();
    start_sign = true;
	tot_r_result = 0;
	for (i = 0; i < RTHD_NUM; i++){
		if (pthread_join(rthd[i], NULL)){ 
			cout<<"pthread_join ERROR"<<endl;
        }
		tot_r_result += r_result[i];
	}
    end_time = getTime();
    elapsed_time = end_time - start_time;

	cout<<tot_r_result<<endl;
	return elapsed_time;
}

void run(){
    int rwlock_type;
	int i;
    acc_timer_t elapsed_time;
    double results[NUM_RWLOCK];
    for (rwlock_type = NO_RWLOCK; rwlock_type != NUM_RWLOCK; rwlock_type++){
        initRecord(&rec, (RWLockType)rwlock_type);
		elapsed_time = 0;
		for (i = 0; i < TEST_CNT; i++){
			elapsed_time += runCase();
		}
		results[rwlock_type] = elapsed_time/1000000.0/TEST_CNT;
    }
    for (rwlock_type = NO_RWLOCK; rwlock_type != NUM_RWLOCK; rwlock_type++){
		cout<<results[rwlock_type]<<"ms"<<endl;
	}
}
