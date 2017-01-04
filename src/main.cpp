#include "eval.h"
#include <stdlib.h>
#include "config.h"

int main(int argc, char* argv[]){
	int num_rthd = DEF_RTHD_NUM;
	int num_wthd = DEF_WTHD_NUM;
	if( argc > 1){ 
		num_rthd = atoi(argv[1]);
	}
	if( argc > 2){ 
		num_wthd = atoi(argv[2]);
	}
    run(num_rthd, num_wthd);
	return 0;
}
