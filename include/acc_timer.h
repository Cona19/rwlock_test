#ifndef _ACC_TIMER
#define _ACC_TIMER
#include <time.h>
#define difftime(s,e) ((e) - (s))
typedef unsigned long acc_timer_t;

acc_timer_t getTime(void);
#endif
