#define _POSIX_SOURCE
#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <fcntl.h>

typedef struct entry entry;
struct entry {
	char *path;
	int want;
} tests[] = {
	{ "testdata", 0 },
	{ "fchdir", ENOTDIR },
	{ "..", 0 },
};

int
main(void)
{
	entry *tt;
	int n, fd, status;

	status = 0;
	for(tt = tests; tt->path; tt++){
		fd = open(tt->path, O_RDONLY);
		if(fd < 0){
			fprintf(stderr, "can't open '%s'\n", tt->path);
			status = 1;
			continue;
		}
		errno = 0;
		n = fchdir(fd);
		close(fd);
		if(errno != tt->want){
			fprintf(stderr, "fchdir(%s) = %d; want %d\n", tt->path, errno, tt->want);
		}
	}
	return 0;
}
