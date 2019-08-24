#include <stdio.h>

int
main(void)
{
	char buf[100];
	int n, want;

	want = 8;
	n = snprintf(NULL, 0, "size %d\n", 10);
	if(n != want)
		fprintf(stderr, "nil: n = %d; want %d\n", n, want);
	n = snprintf(buf, sizeof(buf), "size %d\n", 10);
	if(n != want)
		fprintf(stderr, "buf: n = %d; want %d\n", n, want);
	return 0;
}
