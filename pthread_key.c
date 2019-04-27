#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <pthread.h>
#include <stdarg.h>
#include <unistd.h>

static pthread_key_t key;

void
fatal(int e, char *fmt, ...)
{
	va_list arg;

	va_start(arg, fmt);
	vfprintf(stderr, fmt, arg);
	if(fmt[strlen(fmt)-1] == ':')
		fprintf(stderr, ": %s\n", strerror(e));
	va_end(arg);
	exit(1);
}

void *
fn(void *arg)
{
	pthread_t pid;
	char *s;
	int e;

	pid = pthread_self();
	s = pthread_getspecific(key);
	if(s)
		fatal(0, "pid=%p: already exist '%s'\n", &pid, s);
	e = pthread_setspecific(key, arg);
	if(e != 0)
		fatal(e, "pid=%p: setspecific:", &pid);
	sleep(1);
	s = pthread_getspecific(key);
	printf("pid=%p: %s\n", &pid, s);
	pthread_exit(NULL);

	/* can't reach here */
	abort();
	return NULL;
}

#define nelem(a) (sizeof(a)/sizeof(a[0]))

int
main(void)
{
	int e, i;
	pthread_t pids[3];
	char buf[100];

	e = pthread_key_create(&key, NULL);
	if(e != 0)
		fatal(e, "key_create:");
	for(i = 0; i < nelem(pids); i++){
		snprintf(buf, sizeof(buf), "thread%d", i);
		e = pthread_create(&pids[i], NULL, fn, strdup(buf));
		if(e != 0)
			fatal(e, "create:");
	}
	for(i = 0; i < nelem(pids); i++){
		e = pthread_join(pids[i], NULL);
		if(e != 0)
			fatal(e, "join:");
	}
	e = pthread_key_delete(key);
	if(e != 0)
		fatal(e, "key_delete:");
	return 0;
}
