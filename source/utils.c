#include <stdio.h>
#include <string.h>
#include <ctype.h>
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

uint64_t read_uint64_be(const uint8_t *buffer)
{
    uint32_t high = read_uint32_be(buffer);
    uint32_t low = read_uint32_be(buffer + UINT64_HIGH_OFFSET);

    return ((uint64_t)high << 32) | low;
}

void print_bytes_hex(const uint8_t *buffer, size_t length)
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

void print_payload(const uint8_t *payload, size_t size)
{
    if (payload == NULL || size == 0)
    {
        return;
    }

    printf("Payload (ASCII)\n");
    for (size_t i = 0; i < size; i++)
    {
        char c = (char)payload[i];
        if (c >= PRINTABLE_ASCII_MIN && c <= PRINTABLE_ASCII_MAX)
        {
            printf("%c", c);
        }
        else
        {
            printf(".");
        }
    }
    printf("\n");
}

void print_layer_header(const char *layer_name, const char *protocol_name)
{
    printf("%s\n", layer_name);
    printf("----------\n");
    printf("Protocol : %s\n", protocol_name);
}

size_t extract_line(const uint8_t *buffer, size_t size, char *dest, size_t dest_size)
{
    if (buffer == NULL || size == 0 || dest == NULL || dest_size == 0)
    {
        return 0;
    }

    size_t i = 0;
    while (i < size && i < dest_size - 1)
    {
        if (buffer[i] == '\r' || buffer[i] == '\n')
        {
            break;
        }
        dest[i] = (char)buffer[i];
        i++;
    }

    dest[i] = '\0';
    return i;
}