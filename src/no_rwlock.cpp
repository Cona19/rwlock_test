#include "no_rwlock.h"

NoRWLock::NoRWLock() : RWLock(){
}
NoRWLock::~NoRWLock(){
}
data_t NoRWLock::read(){
	return read_unsafe();
}
void NoRWLock::write(data_t newval){
	write_unsafe(newval);
}
