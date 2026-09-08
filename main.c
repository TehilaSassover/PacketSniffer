#include <stdio.h>
#include <unistd.h>

#include "socket.h"
#include "packet.h"
#include "parser.h"

#define BUFFER_SIZE 65536

/**
 * @file main.c
 * @brief Main entry point for the Packet Sniffer application.
 */

int main(void)
{
    int socket_fd = open_socket();
    if (socket_fd == -1)
    {
        return 1;
    }

    unsigned char buffer[BUFFER_SIZE];
    int packet_size = get_packet(socket_fd, buffer, BUFFER_SIZE);

    if (packet_size == -1)
    {
        close(socket_fd);
        return 1;
    }

    if (!parse_packet(buffer, (size_t)packet_size))
    {
        close(socket_fd);
        return 1;
    }

    close(socket_fd);
    return 0;
}