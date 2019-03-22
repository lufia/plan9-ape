#define _BSD_EXTENSION
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>

typedef struct entry entry;
struct entry {
	int af;
	char *addr;
	socklen_t size;
} tests[] = {
	{ AF_INET, "0.0.0.0", INET_ADDRSTRLEN },
	{ AF_INET, "127.0.0.1", INET_ADDRSTRLEN },
	{ AF_INET, "255.255.255.255", INET_ADDRSTRLEN },
	{ AF_INET6, "::1", INET6_ADDRSTRLEN },
	{ AF_INET6, "2001:db8::123", INET6_ADDRSTRLEN },
	{ 0 },
};

int
main(void)
{
	unsigned char buf[sizeof(struct in6_addr)];
	char s[INET6_ADDRSTRLEN];
	const char *p;
	entry *tt;
	int status;

	status = 0;
	for(tt = tests; tt->af; tt++){
		if(inet_pton(tt->af, tt->addr, buf) <= 0){
			fprintf(stderr, "inet_pton(%d, %s) failed\n", tt->af, tt->addr);
			status = 1;
			continue;
		}
		p = inet_ntop(tt->af, buf, s, tt->size);
		if(p == NULL){
			fprintf(stderr, "inet_ntop(%d, %s) failed\n", tt->af, tt->addr);
			status = 1;
			continue;
		}
		if(strcmp(p, tt->addr) != 0){
			fprintf(stderr, "af=%d, addr=%s: got %s\n", tt->af, tt->addr, p);
			status = 1;
			continue;
		}
	}

	// inet_pton(invalid addr) = 0
	// inet_pton(invalid af) = -1:errno=EAFNOSUPPORT

	// inet_ntop(invalid af) = NULL:errno=EAFNOSUPPORT
	// inet_ntop(insufficient buffer) = NULL:errno=ENOSPC
	return status;
}
