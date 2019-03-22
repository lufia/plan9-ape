#include <stdio.h>
#define _BSD_EXTENSION
#include <stdlib.h>
#include <string.h>
#include <netdb.h>
#include <arpa/inet.h>

typedef struct entry entry;
struct entry {
	int af;
	char *addr;
	unsigned short port;
	char *want;
} tests[] = {
	{ AF_INET, "127.0.0.1", 80, "localhost!http" },
	{ AF_INET6, "::1", 80, "localhost!http" },
	{ 0, NULL, 0, NULL },
};

static char *
getaddr(int af, char *addr, int port)
{
	struct sockaddr_in in4;
	struct sockaddr_in6 in6;
	struct sockaddr *sa;
	char *p, host[NI_MAXHOST], service[NI_MAXSERV];
	const char *msg;
	int n, rv;

	switch(af){
	case AF_INET:
		memset(&in4, 0, sizeof(in4));
		in4.sin_family = af;
		in4.sin_port = htons(port);
		if(inet_pton(af, addr, &in4.sin_addr) <= 0)
			return NULL;
		sa = (struct sockaddr *)&in4;
		n = sizeof(in4);
		break;
	case AF_INET6:
		memset(&in6, 0, sizeof(in6));
		in6.sin6_family = af;
		in6.sin6_port = htons(port);
		if(inet_pton(af, addr, &in6.sin6_addr) <= 0)
			return NULL;
		sa = (struct sockaddr *)&in6;
		n = sizeof(in6);
		break;
	default:
		return NULL;
	}
	rv = getnameinfo(sa, n, host, sizeof(host), service, sizeof(service), 0);
	if(rv != 0){
		msg = gai_strerror(rv);
		fprintf(stderr, "getnameinfo(%s!%d): %s\n", addr, port, msg);
		return NULL;
	}
	p = malloc(strlen(host)+strlen(service)+2);
	if(p == NULL)
		return NULL;
	strcpy(p, host);
	p[strlen(host)] = '!';
	strcpy(p+strlen(host)+1, service);
	p[strlen(host)+strlen(service)+1] = '\0';
	return p;
}

int
main(void)
{
	entry *tt;
	int status, cmp;
	char *addr;

	for(tt = tests; tt->af; tt++){
		addr = getaddr(tt->af, tt->addr, tt->port);
		if(addr == NULL){
			fprintf(stderr, "lookup %s!%d failed\n", tt->addr, tt->port);
			status++;
			continue;
		}
		cmp = strcmp(addr, tt->want);
		free(addr);
		if(cmp != 0){
			fprintf(stderr, "%s!%d -> %s; want %s\n", tt->addr, tt->port, addr, tt->want);
			status++;
			continue;
		}
	}
	return status;
}
