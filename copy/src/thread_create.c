#include "head.h"
pthread_t* thread_create(const char* sfile, const char* dfile, int blocksize, int thread_num) {
	//printf("thread_create()\n");

	pthread_t* tid = (pthread_t*)malloc(sizeof(pthread_t) * thread_num);
	/* 创建线程 */
	int i;

	for (i = 0; i < thread_num; i++) {
		Args* args = (Args*)malloc(sizeof(Args));
		args->sfile = sfile;
		args->dfile = dfile;
		args->blocksize = blocksize;
		args->pos = i * blocksize;
		//printf("Thread %d: \n", flag);
//printf("args: \n\tsfile: %s\n\tdfile: %s\n\tblocksize: %d\n\tpos: %d\n", args->sfile, args->dfile, args->blocksize, args->pos);
		pthread_create(&tid[i], NULL, copy, (void*)args);
	}

    return tid;
}