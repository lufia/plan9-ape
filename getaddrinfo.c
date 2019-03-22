#include <stdio.h>
#define _BSD_EXTENSION
#include <netdb.h>
#include <arpa/inet.h>

typedef struct entry entry;
struct entry {
	char *name;
	char *service;
	char *addr;
	unsigned short port;
} tests[] = {
	{ "localhost", "http", "127.1", 80 },
	{ NULL, NULL, NULL, 0 },
};

static in_port_t
addrstr(int af, struct sockaddr *sa, char *buf, int n)
{
	struct sockaddr_in *in4;
	struct sockaddr_in6 *in6;

	switch(af){
	case AF_INET:
		in4 = (struct sockaddr_in *)sa;
		if(inet_ntop(AF_INET, &in4->sin_addr, buf, n) == NULL)
			return 0;
		return ntohs(in4->sin_port);
	case AF_INET6:
		in6 = (struct sockaddr_in6 *)sa;
		if(inet_ntop(AF_INET6, &in6->sin6_addr, buf, n) == NULL)
			return 0;
		return ntohs(in6->sin6_port);
	default:
		return 0;
	}
}

int
main(void)
{
	entry *tt;
	int status, rv;
	struct addrinfo *p, *q;
	in_port_t port;
	char buf[sizeof(struct in6_addr)];
	const char *msg;

	for(tt = tests; tt->name; tt++){
		rv = getaddrinfo(tt->name, tt->service, NULL, &p);
		if(rv != 0){
			msg = gai_strerror(rv);
			fprintf(stderr, "getaddrinfo(%s): %s\n", tt->addr, msg);
			status++;
			continue;
		}
		printf("%s!%s ->", tt->name, tt->service);
		for(q = p; q != NULL; q = q->ai_next){
			port = addrstr(q->ai_family, q->ai_addr, buf, sizeof(buf));
			if(port == 0){
				fprintf(stderr, "lookup %s!%s failed\n", tt->name, tt->service);
				status++;
				break;
			}
			printf(" %s!%u[proto=%d]", buf, port, q->ai_protocol);
		}
		printf("\n");
		freeaddrinfo(p);
	}
	return status;
}
