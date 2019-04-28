#define _POSIX_SOURCE
#define _PLAN9_SOURCE
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <pthread.h>
#include <stdarg.h>
#include <errno.h>

void
fatal(int e, char *fmt, ...)
{
	va_list arg;

	va_start(arg, fmt);
	vfprintf(stderr, fmt, arg);
	if(fmt[strlen(fmt)-1] == ':')
		fprintf(stderr, " %s\n", strerror(e));
	va_end(arg);
	exit(1);
}

void *
fn(void *arg)
{
	pthread_t *pid, self;

	pid = (pthread_t *)arg;
	self = pthread_self();
	if(!pthread_equal(*pid, self))
		fprintf(stderr, "pthread_self() = %u; want %u\n", self, *pid);
	return NULL;
}

#define nelem(a) (sizeof(a)/sizeof(a[0]))

int
main(void)
{
	int e, i;
	static pthread_t pids[3];

	for(i = 0; i < nelem(pids); i++){
		pids[i] = 0;
		e = pthread_create(&pids[i], NULL, fn, &pids[i]);
		if(e != 0)
			fatal(e, "create:");
	}
	for(i = 0; i < nelem(pids); i++){
		e = pthread_join(pids[i], NULL);
		if(e != 0)
			fatal(e, "join:");
	}
	return 0;
}
