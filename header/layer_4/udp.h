#ifndef UDP_H
#define UDP_H

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

/**
 * @file udp.h
 * @brief UDP (User Datagram Protocol) parser and printer module.
 */

#define UDP_HEADER_SIZE 8

/**
 * @brief Represents a parsed UDP header structure.
 */
typedef struct udp_header {
    uint16_t src_port; /**< Source port */
    uint16_t dst_port; /**< Destination port */
    uint16_t length; /**< Datagram length */
    uint16_t checksum; /**< Checksum */
} udp_header_t;

/**
 * @brief Parses raw bytes into a UDP header structure.
 *
 * @param buffer Pointer to the raw packet bytes.
 * @param packet_size Total available size of the packet.
 * @param header Pointer to the destination udp_header_t structure.
 * @return true if successfully parsed, false otherwise.
 */
bool parse_udp(const uint8_t *buffer, size_t packet_size, udp_header_t *header);

/**
 * @brief Prints parsed UDP header details to standard output.
 *
 * @param header Pointer to the parsed udp_header_t structure.
 */
void print_udp(const udp_header_t *header);

#endif /* UDP_H */