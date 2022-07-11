#include "head.h"

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