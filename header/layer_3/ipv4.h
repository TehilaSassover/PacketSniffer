#ifndef IPV4_H
#define IPV4_H

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

/**
 * @file ipv4.h
 * @brief IPv4 protocol parser and printer module.
 */

#define IPV4_MIN_HEADER_SIZE 20

#define IPV4_VERSION_IHL_OFFSET 0
#define IPV4_DSCP_ECN_OFFSET 1
#define IPV4_TOTAL_LENGTH_OFFSET 2
#define IPV4_IDENTIFICATION_OFFSET 4
#define IPV4_FLAGS_FRAGMENT_OFFSET 6
#define IPV4_TTL_OFFSET 8
#define IPV4_PROTOCOL_OFFSET 9
#define IPV4_CHECKSUM_OFFSET 10
#define IPV4_SOURCE_ADDRESS_OFFSET 12
#define IPV4_DESTINATION_ADDRESS_OFFSET 16

#define IPV4_ADDRESS_SIZE 4

/**
 * @brief Represents a parsed IPv4 header structure.
 */
typedef struct ipv4_header
{
    uint8_t version; /**< IP version (should be 4) */
    uint8_t header_length; /**< Header length in bytes */
    uint8_t dscp; /**< Differentiated Services Code Point */
    uint8_t ecn; /**< Explicit Congestion Notification */
    uint16_t total_length; /**< Total length of the packet */
    uint16_t identification; /**< Identification field */
    uint8_t flags; /**< Flags */
    uint16_t fragment_offset; /**< Fragment offset */
    uint8_t ttl; /**< Time to Live */
    uint8_t protocol; /**< Encapsulated protocol */
    uint16_t header_checksum; /**< Header checksum */
    uint32_t source_address; /**< Source IPv4 address */
    uint32_t destination_address; /**< Destination IPv4 address */
} ipv4_header_t;

/**
 * @brief Parses raw bytes into an IPv4 header structure.
 *
 * @param buffer Pointer to the raw packet bytes.
 * @param packet_size Total available size of the packet.
 * @param header Pointer to the destination ipv4_header_t structure.
 * @return true if successfully parsed, false otherwise.
 */
bool parse_ipv4(
    const uint8_t *buffer,
    size_t packet_size,
    ipv4_header_t *header
);

/**
 * @brief Prints parsed IPv4 header details to standard output.
 *
 * @param header Pointer to the parsed ipv4_header_t structure.
 */
void print_ipv4_header(
    const ipv4_header_t *header
);

#endif /* IPV4_H */