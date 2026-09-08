#ifndef ICMPV6_H
#define ICMPV6_H

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

/**
 * @file icmpv6.h
 * @brief ICMPv6 (Internet Control Message Protocol version 6) parser and printer module.
 */

#define ICMPV6_HEADER_MIN_SIZE 8

#define ICMPV6_TYPE_DEST_UNREACHABLE 1
#define ICMPV6_TYPE_PACKET_TOO_BIG 2
#define ICMPV6_TYPE_TIME_EXCEEDED 3
#define ICMPV6_TYPE_PARAM_PROBLEM 4
#define ICMPV6_TYPE_ECHO_REQUEST 128
#define ICMPV6_TYPE_ECHO_REPLY 129
#define ICMPV6_TYPE_ROUTER_SOLICIT 133
#define ICMPV6_TYPE_ROUTER_ADVERT 134
#define ICMPV6_TYPE_NEIGHBOR_SOLICIT 135
#define ICMPV6_TYPE_NEIGHBOR_ADVERT 136

/**
 * @brief Represents a parsed ICMPv6 header structure.
 */
typedef struct icmpv6_header
{
    uint8_t type; /**< ICMPv6 message type */
    uint8_t code; /**< ICMPv6 message code */
    uint16_t checksum; /**< Header checksum */
    uint16_t rest_of_header_1; /**< Identifier or first part of rest of header */
    uint16_t rest_of_header_2; /**< Sequence number or second part of rest of header */
} icmpv6_header_t;

/**
 * @brief Parses raw bytes into an ICMPv6 header structure.
 *
 * @param buffer Pointer to the raw packet bytes.
 * @param packet_size Total available size of the packet.
 * @param header Pointer to the destination icmpv6_header_t structure.
 * @return true if successfully parsed, false otherwise.
 */
bool parse_icmpv6(
    const uint8_t *buffer,
    size_t packet_size,
    icmpv6_header_t *header
);

/**
 * @brief Prints parsed ICMPv6 header details to standard output.
 *
 * @param header Pointer to the parsed icmpv6_header_t structure.
 */
void print_icmpv6(
    const icmpv6_header_t *header
);

#endif /* ICMPV6_H */