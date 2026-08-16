#ifndef IPV6_H
#define IPV6_H

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#define IPV6_HEADER_SIZE 40

#define IPV6_PAYLOAD_LENGTH_OFFSET 4
#define IPV6_NEXT_HEADER_OFFSET 6
#define IPV6_HOP_LIMIT_OFFSET 7
#define IPV6_SOURCE_ADDRESS_OFFSET 8
#define IPV6_DESTINATION_ADDRESS_OFFSET 24

#define IPV6_VERSION 6

#define IPV6_VERSION_SHIFT 28
#define IPV6_TRAFFIC_CLASS_SHIFT 20
#define IPV6_TRAFFIC_CLASS_MASK 0xFF
#define IPV6_FLOW_LABEL_MASK 0x000FFFFF

typedef struct
{
    uint8_t version;
    uint8_t traffic_class;
    uint32_t flow_label;

    uint16_t payload_length;
    uint8_t next_header;
    uint8_t hop_limit;

    uint8_t source_address[16];
    uint8_t destination_address[16];

} ipv6_header_t;

bool parse_ipv6(
    const uint8_t *buffer,
    size_t packet_size,
    ipv6_header_t *header);

void print_ipv6_header(
    const ipv6_header_t *header);

#endif