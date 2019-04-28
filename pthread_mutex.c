#define _POSIX_SOURCE
#define _PLAN9_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <errno.h>
#include <stdarg.h>

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

int
mutex_init(pthread_mutex_t *mu, int type)
{
	pthread_mutexattr_t attr;

	pthread_mutexattr_init(&attr);
	if(type)
		pthread_mutexattr_settype(&attr, type);
	pthread_mutex_init(mu, &attr);
	pthread_mutexattr_destroy(&attr);
	return 0;
}

void
test1(void)
{
	int e;
	pthread_mutex_t mu;

	mutex_init(&mu, 0);
	e = pthread_mutex_lock(&mu);
	if(e != 0)
		fatal(e, "1.mutex_lock should success:");
	e = pthread_mutex_trylock(&mu);
	if(e != EBUSY)
		fatal(e, "2.mutex_trylock should be busy:");
	pthread_mutex_unlock(&mu);
	pthread_mutex_destroy(&mu);
}

void
test2(void)
{
	int e;
	pthread_mutex_t mu;

	mutex_init(&mu, PTHREAD_MUTEX_RECURSIVE);
	e = pthread_mutex_lock(&mu);
	if(e != 0)
		fatal(e, "1.mutex_lock should success:");
	e = pthread_mutex_trylock(&mu);
	if(e != 0)
		fatal(e, "2.mutex_trylock should success:");
	e = pthread_mutex_lock(&mu);
	if(e != 0)
		fatal(e, "3.mutex_lock should success:");
	pthread_mutex_unlock(&mu);
	pthread_mutex_unlock(&mu);
	pthread_mutex_unlock(&mu);
	pthread_mutex_destroy(&mu);
}

void (*tests[])(void) = {
	test1,
	test2,
	NULL,
};

int
main(void)
{
	void (**p)(void);

	for(p = tests; *p; p++)
		(*p)();
	return 0;
}
