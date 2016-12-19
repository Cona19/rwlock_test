#include "acc_timer.h"

/*
 * CLOCK_PROCESS_CPUTIME_ID
 * CLOCK_THREAD_CPUTIME_ID
 */
acc_timer_t getTime(void){
	timespec ts;
	clock_gettime(CLOCK_REALTIME, &ts);
	return ts.tv_sec * 1000000000UL + ts.tv_nsec;
}
/*
int main(){
	printf("%lu\n", gettime());
	return 0;
}
*/
