#include "swarm_client.h"

void __attribute__((__noreturn__))
die(int e, const char *msg)
{

    if (msg)
        warnx("%s: %d", msg, e);
    rump_sys_reboot(0, NULL);
    exit(e);
}

void init_swarm_client() {
    rump_init();

    int e;
	if ((e = rump_pub_netconfig_ifcreate("virt0")) != 0)
		die(e, "create virt0");
	if ((e = rump_pub_netconfig_dhcp_ipv4_oneshot("virt0")) != 0)
		die(e, "dhcp address");
}

ssize_t rump_sys_send(int sockfd, const void *buf, size_t len, int flags) {
    return rump_sys_sendto(sockfd, buf, len, flags, NULL, 0);
}

ssize_t rump_sys_recv(int sockfd, void *buf, size_t len, int flags) {
    return rump_sys_recvfrom(sockfd, buf, len, flags, NULL, 0);
}

