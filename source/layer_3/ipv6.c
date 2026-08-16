#include <stdio.h>
#include <string.h>
#include <arpa/inet.h>

#include "layer_3/ipv6.h"
#include "utils.h"


bool parse_ipv6(
    const uint8_t *buffer,
    size_t packet_size,
    ipv6_header_t *header)
{
    if (buffer == NULL ||
        header == NULL ||
        packet_size < IPV6_HEADER_SIZE)
    {
        return false;
    }

    uint32_t first_word;

    memcpy(
        &first_word,
        buffer,
        sizeof(first_word));

    first_word = ntohl(first_word);

    header->version =
        (first_word >> IPV6_VERSION_SHIFT) & 0x0F;

    header->traffic_class =
        (first_word >> IPV6_TRAFFIC_CLASS_SHIFT) & IPV6_TRAFFIC_CLASS_MASK;

    header->flow_label =
        first_word & IPV6_FLOW_LABEL_MASK;

    header->payload_length =
        read_uint16_be(
            buffer + IPV6_PAYLOAD_LENGTH_OFFSET);

    header->next_header =
        buffer[IPV6_NEXT_HEADER_OFFSET];

    header->hop_limit =
        buffer[IPV6_HOP_LIMIT_OFFSET];

    memcpy(
        header->source_address,
        buffer + IPV6_SOURCE_ADDRESS_OFFSET,
        sizeof(header->source_address));

    memcpy(
        header->destination_address,
        buffer + IPV6_DESTINATION_ADDRESS_OFFSET,
        sizeof(header->destination_address));

    return true;
}

void print_ipv6_header(
    const ipv6_header_t *header)
{
    if (header == NULL)
    {
        return;
    }

    char source_ip[INET6_ADDRSTRLEN];
    char destination_ip[INET6_ADDRSTRLEN];

    inet_ntop(
        AF_INET6,
        header->source_address,
        source_ip,
        sizeof(source_ip));

    inet_ntop(
        AF_INET6,
        header->destination_address,
        destination_ip,
        sizeof(destination_ip));

    printf("Layer 3\n");
    printf("--------\n");

    printf("Protocol          : IPv6\n");
    printf("Version           : %u\n",
           header->version);

    printf("Traffic Class     : %u\n",
           header->traffic_class);

    printf("Flow Label        : %u\n",
           header->flow_label);

    printf("Payload Length    : %u\n",
           header->payload_length);

    printf("Next Header       : %u\n",
           header->next_header);

    printf("Hop Limit         : %u\n",
           header->hop_limit);

    printf("Source IP         : %s\n",
           source_ip);

    printf("Destination IP    : %s\n",
           destination_ip);
}