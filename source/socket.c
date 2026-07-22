#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <net/ethernet.h>
#include <unistd.h>

#include "../header/socket.h"


int open_socket()
{
    int sock_r = socket(AF_PACKET, SOCK_RAW, htons(ETH_P_ALL));

    if (sock_r < 0)
    {
        perror("Error opening socket");
        return -1;
    }

    printf("Socket opened successfully! Waiting for a packet...\n");

    return sock_r;
}


int get_packet(int sock_r, unsigned char *buffer, int buffer_size)
{
    struct sockaddr saddr;
    socklen_t saddr_len = sizeof(saddr);

    int buflen = recvfrom(
        sock_r,
        buffer,
        buffer_size,
        0,
        &saddr,
        &saddr_len
    );

    if (buflen < 0)
    {
        perror("Error in recvfrom");
        return -1;
    }

    return buflen;
}