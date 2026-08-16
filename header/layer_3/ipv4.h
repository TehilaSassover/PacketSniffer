#ifndef IPV4_H
#define IPV4_H

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#define IPV4_MIN_HEADER_SIZE 20

#define IPV4_VERSION 4

#define IPV4_VERSION_IHL_OFFSET        0
#define IPV4_DSCP_ECN_OFFSET           1
#define IPV4_TOTAL_LENGTH_OFFSET       2
#define IPV4_IDENTIFICATION_OFFSET     4
#define IPV4_FLAGS_FRAGMENT_OFFSET     6
#define IPV4_TTL_OFFSET                8
#define IPV4_PROTOCOL_OFFSET           9
#define IPV4_HEADER_CHECKSUM_OFFSET    10
#define IPV4_SOURCE_IP_OFFSET          12
#define IPV4_DESTINATION_IP_OFFSET     16
#define IPV4_OPTIONS_OFFSET            20

#define IPV4_VERSION_SHIFT 4
#define IPV4_DSCP_SHIFT 2

#define IPV4_ECN_MASK 0x03

#define IPV4_FLAGS_SHIFT 13
#define IPV4_FLAGS_MASK 0x07

#define IPV4_FRAGMENT_OFFSET_MASK 0x1FFF


typedef struct ipv4_header
{
    uint8_t version;
    uint8_t header_length;

    uint8_t dscp;
    uint8_t ecn;

    uint16_t total_length;

    uint16_t identification;

    uint8_t flags;
    uint16_t fragment_offset;

    uint8_t ttl;
    uint8_t protocol;

    uint16_t header_checksum;

    uint32_t source_ip;
    uint32_t destination_ip;

    const uint8_t *options;
    size_t options_length;

} ipv4_header_t;


bool parse_ipv4(
    const uint8_t *buffer,
    size_t packet_size,
    ipv4_header_t *header
);

#endif