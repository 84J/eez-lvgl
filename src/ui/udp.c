#include "udp.h"
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

void udp_send(const char* msg)
{
    printf("[UDP]: Send %s\n", msg);

    int sock = socket(AF_INET, SOCK_DGRAM, 0);
    if (sock < 0) {
        perror("socket");
        return;
    }

    struct sockaddr_in addr;
    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port = htons(46666);
    addr.sin_addr.s_addr = inet_addr("192.168.66.10");

    ssize_t sent = sendto(sock, msg, strlen(msg), 0, (struct sockaddr*)&addr, sizeof(addr));
    if (sent < 0) {
        perror("sendto");
    } else {
        // printf("Sent %zd bytes to 192.168.66.10:46666\n", sent);
    }

    close(sock);
}

void udp_send_opt_entered(void)
{
    udp_send("L-OP,100");
    udp_send("L-BK,100");
}

void udp_send_opt_exited(void)
{
    udp_send("L-OP,20");
    udp_send("L-BK,20");
}
