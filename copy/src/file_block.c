#include "head.h"
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