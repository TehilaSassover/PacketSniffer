#include <stdio.h>
#include <string.h>
#include <arpa/inet.h>
#include "layer_4/udp.h"

bool parse_udp(const uint8_t *buffer, size_t packet_size, udp_header_t *header)
{
    if (buffer == NULL || header == NULL || packet_size < UDP_HEADER_SIZE)
    {
        return false;
    }

    uint16_t raw_src_port, raw_dst_port, raw_length, raw_checksum;

    memcpy(&raw_src_port, buffer + 0, sizeof(raw_src_port));
    memcpy(&raw_dst_port, buffer + 2, sizeof(raw_dst_port));
    memcpy(&raw_length,   buffer + 4, sizeof(raw_length));
    memcpy(&raw_checksum, buffer + 6, sizeof(raw_checksum));

    header->src_port = ntohs(raw_src_port);
    header->dst_port = ntohs(raw_dst_port);
    header->length   = ntohs(raw_length);
    header->checksum = ntohs(raw_checksum);

    return true;
}

void print_udp(const udp_header_t *header)
{
    if (header == NULL)
    {
        return;
    }

    printf("Layer 4\n");
    printf("--------\n");
    printf("Protocol        : UDP\n");
    printf("Source Port     : %u\n", header->src_port);
    printf("Destination Port: %u\n", header->dst_port);
    printf("Length          : %u bytes\n", header->length);
    printf("Checksum        : 0x%04X\n", header->checksum);
}