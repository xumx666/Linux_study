#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
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

int pram_check(int argc, const char* sfile, int thread_num);

int file_block(const char* sfile, int thread_num);

void* copy(void* args);

pthread_t* thread_create(const char* sfile, const char* dfile, int blocksize, int thread_num);

int thread_join(pthread_t* tid, int thread_num);


