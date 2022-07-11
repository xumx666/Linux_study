#include "head.h"
int main(int argc, char** argv) {

	int thread_num;
	
	if (argv[3] == 0) {
		thread_num = 3;
	}
	else  {
		thread_num = atoi(argv[3]);
	}
	
	pram_check(argc, argv[1], thread_num);

	int blocksize;

	blocksize = file_block(argv[1], thread_num);
	//printf("block size = %d\n", blocksize);

	pthread_t* tid = thread_create(argv[1], argv[2], blocksize, thread_num);

	// for (int i = 0; i < thread_num; i++) {
	// 	pthread_join(tid[i], NULL);
	// }
	thread_join(tid, thread_num);
	
	printf("ok\n");
	return 0;
}