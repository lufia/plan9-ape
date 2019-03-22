#define _PLAN9_SOURCE
#include <stdio.h>
#include <lib9.h>

int
main(void)
{
	printf("%lld\n", nsec());
	return 0;
}
