#include <stdio.h>
#include <string.h>
#include <arpa/inet.h>

#include "../header/utils.h"

void print_mac(const unsigned char *mac)
{
    for (int i = 0; i < MAC_ADDRESS_SIZE; i++)
    {
        printf("%02X", mac[i]);

        if (i < MAC_ADDRESS_SIZE - 1)
        {
            printf(":");
        }
    }
}

void print_ipv4(const uint8_t *ip)
{
    printf(
        "%u.%u.%u.%u",
        ip[0],
        ip[1],
        ip[2],
        ip[3]);
}

uint16_t read_uint16_be(const uint8_t *buffer)
{
    uint16_t value;

    memcpy(&value, buffer, sizeof(value));

    return ntohs(value);
}

uint32_t read_uint32_be(const uint8_t *buffer)
{
    uint32_t value;

    memcpy(&value, buffer, sizeof(value));

    return ntohl(value);
}

void print_bytes_hex(
    const uint8_t *buffer,
    size_t length)
{
    for (size_t i = 0; i < length; i++)
    {
        printf("%02X", buffer[i]);

        if (i < length - 1)
        {
            printf(" ");
        }
    }
}