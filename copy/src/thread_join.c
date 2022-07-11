#include "head.h"
int thread_join(pthread_t* tid, int thread_num) {
	for (int i = 0; i < thread_num; i++) {
		pthread_join(tid[i], NULL);
	}
	free(tid);
	tid = NULL;
	return 0;
}