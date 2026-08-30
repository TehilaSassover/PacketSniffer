#ifndef ICMPV6_H
#define ICMPV6_H

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

/* ICMPv6 Protocol Constants */
#define ICMPV6_HEADER_MIN_SIZE 8

/* ICMPv6 Message Types */
#define ICMPV6_TYPE_DEST_UNREACHABLE    1
#define ICMPV6_TYPE_PACKET_TOO_BIG      2
#define ICMPV6_TYPE_TIME_EXCEEDED       3
#define ICMPV6_TYPE_PARAM_PROBLEM       4
#define ICMPV6_TYPE_ECHO_REQUEST        128
#define ICMPV6_TYPE_ECHO_REPLY          129
#define ICMPV6_TYPE_ROUTER_SOLICIT      133
#define ICMPV6_TYPE_ROUTER_ADVERT       134
#define ICMPV6_TYPE_NEIGHBOR_SOLICIT    135
#define ICMPV6_TYPE_NEIGHBOR_ADVERT     136

typedef struct {
    uint8_t  type;
    uint8_t  code;
    uint16_t checksum;
    uint16_t rest_of_header_1;
    uint16_t rest_of_header_2;
} icmpv6_header_t;

bool parse_icmpv6(const uint8_t *buffer, size_t packet_size, icmpv6_header_t *header);
void print_icmpv6(const icmpv6_header_t *header);

#endif /* ICMPV6_H */