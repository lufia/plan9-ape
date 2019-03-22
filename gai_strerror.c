#define _BSD_EXTENSION
#include <stdio.h>
#include <string.h>
#include <netdb.h>

typedef struct entry entry;
struct entry {
	int e;
	const char *s;
} tests[] = {
	{ EAI_BADFLAGS, "bad flags" },
	{ EAI_NONAME, "authoratitive negative response" },
	{ EAI_AGAIN, "temporary lookup failure" },
	{ EAI_FAIL, "name resolution failure" },
	{ EAI_FAMILY, "family not supported" },
	{ EAI_SOCKTYPE, "ai_socktype not supported" },
	{ EAI_SERVICE, "srvname unsupported" },
	{ EAI_MEMORY, "no memory" },
	{ EAI_SYSTEM, "see errno" },
	{ EAI_OVERFLOW, "overflow" },
	{ 0, NULL },
};

int
main(void)
{
	entry *tt;
	const char *s;
	int status;

	status = 0;
	for(tt = tests; tt->e; tt++){
		s = gai_strerror(tt->e);
		if(strcmp(s, tt->s) != 0){
			fprintf(stderr, "gai_strerror(%d) = '%s'; want '%s'\n", tt->e, s, tt->s);
			status = 1;
		}
	}
	return status;
}
