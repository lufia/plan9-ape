#include <stdio.h>
#define _BSD_EXTENSION
#include <stdlib.h>
#include <string.h>

enum {
	N = 1<<16,
	M = 2,
};

int
main(void)
{
	unsigned int n, results[N];
	int i, bloat, high;

	memset(results, 0, sizeof(results));
	for(i = 0; i < N*M; i++)
		results[arc4random() % N]++;
	bloat = 0;
	high = 0;
	for(i = 0; i < N; i++){
		if(results[i] > high)
			high = results[i];
		if(results[i] > M*3)
			bloat++;
	}
	fprintf(stderr, "high = %d, bloat = %d/%d\n", high, bloat, N);
	return 0;
}
