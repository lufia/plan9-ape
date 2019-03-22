#define _POSIX_SOURCE
#include <stdio.h>
#include <unistd.h>

typedef struct entry entry;
struct entry {
	int conf;
	long v;
} tests[] = {
	{ _SC_PAGESIZE, 4096 },
	{ 0, 0 },
};

int
main(void)
{
	entry *tt;
	long v;
	int status;

	status = 0;
	for(tt = tests; tt->conf; tt++){
		v = sysconf(tt->conf);
		if(v != tt->v){
			fprintf(stderr, "sysconf(%d) = %ld; want %ld\n", tt->conf, v, tt->v);
			status = 1;
		}
	}
	return status;
}
