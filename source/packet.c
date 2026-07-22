#include <stdio.h>
#include "../header/packet.h"


void print_packet(unsigned char *buffer, int length)
{
    printf("\n--- Packet Content (%d bytes) ---\n", length);

    for (int i = 0; i < length; i++)
    {
        printf("%02X ", buffer[i]);

        if ((i + 1) % 16 == 0)
        {
            printf("\n");
        }
    }

    printf("\n--------------------------------\n");
}