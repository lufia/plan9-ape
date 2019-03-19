#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <libgen.h>

typedef struct entry entry;
struct entry {
	char *path;
	char *dir;
	char *file;
} tests[] = {
	{ "", ".", "." },
	{ NULL, ".", "." },
	{ "test.c", ".", "test.c" },
	{ "/", "/", "/" },
	{ "bin/ls", "bin", "ls" },
	{ "usr/bin/ls", "usr/bin", "ls" },
	{ "/bin/ls", "/bin", "ls" },
	{ "/usr/bin/ls", "/usr/bin", "ls" },
	{ "/bin//", "/", "bin" },
	{ "/bin//pwd", "/bin", "pwd" },
};

#define nelem(a) (sizeof(a)/sizeof((a)[0]))

int
main(void)
{
	char *s, *p;
	entry *tt, *e;

	e = tests+nelem(tests);
	for(tt = tests; tt < e; tt++){
		if(tt->path == NULL)
			s = NULL;
		else
			s = strdup(tt->path);
		p = basename(s);
		if(strcmp(p, tt->file) != 0)
			fprintf(stderr, "basename(%s) = %s; want %s\n", tt->path, p, tt->file);
		p = dirname(s);
		if(strcmp(p, tt->dir) != 0)
			fprintf(stderr, "dirname(%s) = %s; want %s\n", tt->path, p, tt->dir);
		free(s);
	}
	return 0;
}
