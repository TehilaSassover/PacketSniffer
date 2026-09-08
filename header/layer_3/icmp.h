#ifndef ICMP_H
#define ICMP_H

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

/**
 * @file icmp.h
 * @brief ICMP (Internet Control Message Protocol) parser and printer module.
 */

#define ICMP_HEADER_MIN_SIZE 8

#define ICMP_TYPE_ECHO_REPLY 0
#define ICMP_TYPE_DEST_UNREACHABLE 3
#define ICMP_TYPE_REDIRECT 5
#define ICMP_TYPE_ECHO_REQUEST 8
#define ICMP_TYPE_TIME_EXCEEDED 11

/**
 * @brief Represents a parsed ICMP header structure.
 */
typedef struct icmp_header
{
    uint8_t type; /**< ICMP message type */
    uint8_t code; /**< ICMP message code */
    uint16_t checksum; /**< Header checksum */
    uint16_t rest_of_header_1; /**< Identifier or first part of rest of header */
    uint16_t rest_of_header_2; /**< Sequence number or second part of rest of header */
} icmp_header_t;

/**
 * @brief Parses raw bytes into an ICMP header structure.
 *
 * @param buffer Pointer to the raw packet bytes.
 * @param packet_size Total available size of the packet.
 * @param header Pointer to the destination icmp_header_t structure.
 * @return true if successfully parsed, false otherwise.
 */
bool parse_icmp(
    const uint8_t *buffer,
    size_t packet_size,
    icmp_header_t *header
);

/**
 * @brief Prints parsed ICMP header details to standard output.
 *
 * @param header Pointer to the parsed icmp_header_t structure.
 */
void print_icmp(
    const icmp_header_t *header
);

#endif /* ICMP_H */