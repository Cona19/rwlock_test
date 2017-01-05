#include "record.h"

void Record::initialize(data_t dat1, data_t dat2){
    this->dat1 = dat1;
    this->dat2 = dat2;
}

void Record::write(data_t newval){
	data_t tmp;
	tmp = this->dat1 + newval;
	this->dat1 = this->dat2 - newval;
    this->dat2 = tmp;
}

data_t Record::read(){
    return dat1 + dat2;
}

Record::Record(){
    this->dat1 = this->dat2 = 0;
}

Record::~Record(){
}

