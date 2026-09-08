#ifndef IPV6_H
#define IPV6_H

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

/**
 * @file ipv6.h
 * @brief IPv6 protocol parser and printer module.
 */

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

/**
 * @brief Represents a parsed IPv6 header structure.
 */
typedef struct ipv6_header
{
    uint8_t version; /**< IP version (should be 6) */
    uint8_t traffic_class; /**< Traffic class */
    uint32_t flow_label; /**< Flow label */
    uint16_t payload_length; /**< Payload length */
    uint8_t next_header; /**< Next header / protocol */
    uint8_t hop_limit; /**< Hop limit */
    uint8_t source_address[16]; /**< Source IPv6 address */
    uint8_t destination_address[16]; /**< Destination IPv6 address */
} ipv6_header_t;

/**
 * @brief Parses raw bytes into an IPv6 header structure.
 *
 * @param buffer Pointer to the raw packet bytes.
 * @param packet_size Total available size of the packet.
 * @param header Pointer to the destination ipv6_header_t structure.
 * @return true if successfully parsed, false otherwise.
 */
bool parse_ipv6(
    const uint8_t *buffer,
    size_t packet_size,
    ipv6_header_t *header
);

/**
 * @brief Prints parsed IPv6 header details to standard output.
 *
 * @param header Pointer to the parsed ipv6_header_t structure.
 */
void print_ipv6_header(
    const ipv6_header_t *header
);

#endif /* IPV6_H */