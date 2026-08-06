#include <stdio.h>
#include <unistd.h>

#include "../header/socket.h"
#include "../header/packet.h"
#include "../header/parser.h"

#define BUFFER_SIZE 65536

int main()
{
    int socket_r = open_socket();

    if (socket_r == -1)
    {
        return 1;
    }

    unsigned char buffer[BUFFER_SIZE];

    int packet_size = get_packet(
        socket_r,
        buffer,
        BUFFER_SIZE);

    if (packet_size == -1)
    {
        close(socket_r);
        return 1;
    }

    if (!parse_packet(buffer, packet_size))
    {
        close(socket_r);
        return 1;
    }

    close(socket_r);

    return 0;
}