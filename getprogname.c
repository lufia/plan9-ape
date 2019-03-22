#define _BSD_EXTENSION
#include <stdio.h>
#include <stdlib.h>

int
main(void)
{
	const char *s;

	s = getprogname();
	printf("progname() = %s\n", s);
	setprogname("testprog");
	s = getprogname();
	printf("progname() = %s\n", s);
	return 0;
}
