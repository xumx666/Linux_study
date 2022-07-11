#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <string.h>
#include <pthread.h>

typedef struct {
	char* sfile;
	char* dfile;
	int blocksize;
	int pos;
}Args;

int pram_check(int argc, const char* sfile, int thread_num) {
	
	if (argc < 3) {
		printf("error: 缺少参数\n");
		exit(0);
	}
	if ((access(sfile, F_OK)) != 0) {
		printf("error: 源文件不正确或不存在\n");
		exit(0);
	}
	if (thread_num <= 0 || thread_num > 100) {
		printf("error: 进程数量不允许小于0或大于100\n");
		exit(0);
	}
	//printf("check ok\n");
	return 0;
}

int file_block(const char* sfile, int thread_num) {
	int fd = open(sfile, 0, O_RDONLY);
	int fsize = lseek(fd, 0, SEEK_END);
	if (fsize % thread_num == 0) {
		return fsize / thread_num;
	}
	else {
		return fsize / thread_num + 1;
	}
}

// const char* sfile, const char* dfile, int block_size, int copy_pos
void* copy(void* args) {
	//printf("copy()\n");
	Args* a = (Args*)args;
	//printf("args: \n\tsfile: %s\n\tdfile: %s\n\tblocksize: %d\n\tpos: %d\n", a->sfile, a->dfile, a->blocksize, a->pos);
	char buffer[a->blocksize];
	bzero(buffer, sizeof(buffer));
	ssize_t readlen;
	int sfd = open(a->sfile, O_RDONLY);
	int dfd = open(a->dfile, O_RDWR|O_CREAT, 0664);

	lseek(sfd, a->pos, SEEK_SET);
	lseek(dfd, a->pos, SEEK_SET);

    	readlen = read(sfd,buffer,sizeof(buffer));
    	write(dfd,buffer,readlen);

    	close(sfd);
    	close(dfd);
	free(args);
	args = NULL;
	a = NULL;
	return 0;
}


int thread_create(const char* sfile, const char* dfile, int blocksize, int thread_num) {
	//printf("thread_create()\n");

    pthread_t tid[thread_num];
	/* 创建线程 */
	int flag;

	for (flag = 0; flag < thread_num; flag++) {
		Args* args = (Args*)malloc(sizeof(Args));
		args->sfile = sfile;
		args->dfile = dfile;
		args->blocksize = blocksize;
		args->pos = flag * blocksize;
		//printf("Thread %d: \n", flag);
//printf("args: \n\tsfile: %s\n\tdfile: %s\n\tblocksize: %d\n\tpos: %d\n", args->sfile, args->dfile, args->blocksize, args->pos);
		pthread_create(&tid[flag], NULL, copy, (void*)args);
	}
	for (flag = 0; flag < thread_num; flag++) {

		pthread_join(tid[flag], NULL);
	}
    return 0;
}


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

	thread_create(argv[1], argv[2], blocksize, thread_num);

	
	printf("ok\n");
	return 0;
}
