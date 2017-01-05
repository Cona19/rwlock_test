#ifndef _RECORD
#define _RECORD

typedef unsigned long data_t;

class Record{
private:
    data_t dat1;
    data_t dat2;
public:
    Record();
    ~Record();
    void write(data_t newval);
    data_t read();
    void initialize(data_t dat1, data_t dat2);
};
#endif
