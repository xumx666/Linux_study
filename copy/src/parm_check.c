#include "head.h"

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