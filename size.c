#include <stdio.h>
#include <unistd.h>
#include <time.h>

int
main(void)
{
	printf("sizeof int = %d\n", sizeof(int));
	printf("sizeof short = %d\n", sizeof(short));
	printf("sizeof long = %d\n", sizeof(long));
	printf("sizeof off_t = %d\n", sizeof(off_t));
	printf("sizeof size_t = %d\n", sizeof(size_t));
	printf("sizeof time_t = %d\n", sizeof(time_t));
	return 0;
}
