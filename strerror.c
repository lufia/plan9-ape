#include <stdio.h>
#include <string.h>
#include <errno.h>

typedef struct entry entry;
struct entry {
	int e;
	const char *s;
} tests[] = {
	{ ETXTBSY, "Text file is busy" },
	{ EALREADY, "Operation already in progress" },
 	{ ECONNRESET, "Connection reset by peer" },
	{ EOVERFLOW, "Value too large for defined data type" },
	{ 0, NULL },
};

int
main(void)
{
	int status;
	entry *tt;
	const char *s;

	status = 0;
	for(tt = tests; tt->e; tt++){
		s = strerror(tt->e);
		if(strcmp(s, tt->s) != 0){
			fprintf(stderr, "strerror(%d) = '%s'; want '%s'\n", tt->e, s, tt->s);
			status = 1;
		}
	}
	return status;
}
