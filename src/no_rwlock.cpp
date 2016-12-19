#include "no_rwlock.h"

NoRWLock::NoRWLock() : RWLock(){
}
NoRWLock::~NoRWLock(){
}
void NoRWLock::RLock(){
}
void NoRWLock::RUnlock(){
}
void NoRWLock::WLock(){
}
void NoRWLock::WUnlock(){
}
