#include "rwlock.h"

RWLock::RWLock(){
}
RWLock::~RWLock(){
}
data_t RWLock::read(){
	return 0;
}
void RWLock::write(data_t newval){
}
void RWLock::initialize(data_t dat1, data_t dat2){
	rec.initialize(dat1, dat2);
}

data_t RWLock::read_unsafe(){
	return rec.read();
}
void RWLock::write_unsafe(data_t newval){
	rec.write(newval);
}
