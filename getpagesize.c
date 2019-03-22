#define _POSIX_SOURCE
#define _BSD_EXTENSION
#include <stdio.h>
#include <unistd.h>

int
main(void)
{
	long w;
	int v;

	v = getpagesize();
	w = sysconf(_SC_PAGESIZE);
	if(v != tt->v){
		fprintf(stderr, "getpagesize() = %d; want %ld\n", v, w);
		return 1;
	}
	return 0;
}
