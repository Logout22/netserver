#include <inttypes.h>
#include <err.h>
#include <errno.h>
#include <netdb.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stropts.h>

#include <rump/rump.h>
#include <rump/netconfig.h>
#include <rump/rump_syscalls.h>
#include <rump/rumpnet_if_pub.h>
#include <rump/rumpdefs.h>

#include <sys/cdefs.h>
#include <sys/stat.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <netinet/in.h>
#include <arpa/inet.h>

void __attribute__((__noreturn__)) die(int e, const char *msg);
void init_swarm_client();
ssize_t rump_sys_send(int sockfd, const void *buf, size_t len, int flags);
ssize_t rump_sys_recv(int sockfd, void *buf, size_t len, int flags);

