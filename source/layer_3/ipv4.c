#include <stdio.h>
#include <string.h>
#include <arpa/inet.h>

#include "layer_3/ipv4.h"
#include "utils.h"

bool parse_ipv4(
    const uint8_t *buffer,
    size_t packet_size,
    ipv4_header_t *header)
{
    if (buffer == NULL ||
        header == NULL ||
        packet_size < IPV4_MIN_HEADER_SIZE)
    {
        return false;
    }

    uint8_t version_ihl = buffer[IPV4_VERSION_IHL_OFFSET];
    uint8_t dscp_ecn = buffer[IPV4_DSCP_ECN_OFFSET];

    header->version =
        (version_ihl >> 4) & 0x0F;

    header->header_length =
        version_ihl & 0x0F;

    header->dscp =
        (dscp_ecn >> 2) & 0x3F;

    header->ecn =
        dscp_ecn & 0x03;

    header->total_length =
        read_uint16_be(
            buffer + IPV4_TOTAL_LENGTH_OFFSET);

    header->identification =
        read_uint16_be(
            buffer + IPV4_IDENTIFICATION_OFFSET);

    uint16_t flags_fragment =
        read_uint16_be(
            buffer + IPV4_FLAGS_FRAGMENT_OFFSET);

    header->flags =
        (flags_fragment >> 13) & 0x07;

    header->fragment_offset =
        flags_fragment & 0x1FFF;

    header->ttl =
        buffer[IPV4_TTL_OFFSET];

    header->protocol =
        buffer[IPV4_PROTOCOL_OFFSET];

    header->header_checksum =
        read_uint16_be(
            buffer + IPV4_CHECKSUM_OFFSET);

    memcpy(
        &header->source_address,
        buffer + IPV4_SOURCE_ADDRESS_OFFSET,
        sizeof(header->source_address));

    memcpy(
        &header->destination_address,
        buffer + IPV4_DESTINATION_ADDRESS_OFFSET,
        sizeof(header->destination_address));

    return true;
}

void print_ipv4_header(
    const ipv4_header_t *header)
{
    if (header == NULL)
    {
        return;
    }

    char source_ip[INET_ADDRSTRLEN];
    char destination_ip[INET_ADDRSTRLEN];

    inet_ntop(
        AF_INET,
        &header->source_address,
        source_ip,
        sizeof(source_ip));

    inet_ntop(
        AF_INET,
        &header->destination_address,
        destination_ip,
        sizeof(destination_ip));

    printf("Layer 3\n");
    printf("--------\n");

    printf("Protocol          : IPv4\n");
    printf("Version           : %u\n", header->version);
    printf("Header Length     : %u bytes\n",
           header->header_length * 4);
    printf("DSCP              : %u\n", header->dscp);
    printf("ECN               : %u\n", header->ecn);
    printf("Total Length      : %u\n", header->total_length);
    printf("Identification    : %u\n", header->identification);
    printf("Flags             : 0x%X\n", header->flags);
    printf("Fragment Offset   : %u\n",
           header->fragment_offset);
    printf("TTL               : %u\n", header->ttl);
    printf("Protocol          : %u\n", header->protocol);
    printf("Header Checksum   : 0x%04X\n",
           header->header_checksum);
    printf("Source IP         : %s\n", source_ip);
    printf("Destination IP    : %s\n", destination_ip);
}
