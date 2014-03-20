#include "swarm_client.h"

static int unix_socket = -1;

void __attribute__((__noreturn__))
die(int e, const char *msg)
{

    if (msg)
        warnx("%s: %d", msg, e);
    exit(e);
}

void exit_handler() {
    rump_sys_reboot(0, NULL);
    if (unix_socket >= 0) {
        close(unix_socket);
    }
}

void init_swarm_client() {
    rump_init();
    atexit(exit_handler);
    unix_socket = socket(AF_UNIX, SOCK_STREAM, 0);
    if (!unix_socket) {
        die(errno, "socket");
    }

    struct sockaddr_un sockaddr = {
        .sun_family = AF_UNIX,
        .sun_path = SOCK_FN,
    };
    if (connect(unix_socket,
                (struct sockaddr *)&sockaddr,
                sizeof(sockaddr))) {
        die(errno, "connect");
    }

    // initialise swarm_ipc
    sipc_client_set_socket(unix_socket);

    if (request_swarm_getshm()) {
        die(errno, "payload");
    }

    if (rcv_message_type_sock() != SWARM_GETSHM_REPLY) {
        die(errno, "reply");
    }

    char *filename;
    in_addr_t ip_address;
    if (rcv_reply_swarm_getshm(&ip_address, &filename) < 0) {
        die(errno, "read");
    }

    // bus file must be local and stat()-able
    struct stat statstruct = {};
    if (stat(filename, &statstruct) != 0) {
        die(errno, "stat");
    }

    rump_pub_shmif_create(filename, 0);
    free(filename);

    char const *ip_address_str = inet_ntoa(
            (struct in_addr) { .s_addr = ip_address } );
    rump_pub_netconfig_ipv4_ifaddr(
            "shmif0", ip_address_str, "0.0.0.0");
    rump_pub_netconfig_ifup("shmif0");
}

ssize_t rump_sys_send(int sockfd, const void *buf, size_t len, int flags) {
    return rump_sys_sendto(sockfd, buf, len, flags, NULL, 0);
}

ssize_t rump_sys_recv(int sockfd, void *buf, size_t len, int flags) {
    return rump_sys_recvfrom(sockfd, buf, len, flags, NULL, 0);
}

