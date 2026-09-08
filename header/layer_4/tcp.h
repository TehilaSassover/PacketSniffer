#ifndef TCP_H
#define TCP_H

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

/**
 * @file tcp.h
 * @brief TCP (Transmission Control Protocol) parser and printer module.
 */

#define TCP_HEADER_MIN_SIZE 20

/* TCP Flags Bitmasks */
#define TCP_FLAG_FIN 0x01
#define TCP_FLAG_SYN 0x02
#define TCP_FLAG_RST 0x04
#define TCP_FLAG_PSH 0x08
#define TCP_FLAG_ACK 0x10
#define TCP_FLAG_URG 0x20
#define TCP_FLAG_ECE 0x40
#define TCP_FLAG_CWR 0x80

/**
 * @brief Represents a parsed TCP header structure.
 */
typedef struct tcp_header {
    uint16_t src_port; /**< Source port */
    uint16_t dst_port; /**< Destination port */
    uint32_t seq_num; /**< Sequence number */
    uint32_t ack_num; /**< Acknowledgment number */
    uint8_t data_offset; /**< Header length in bytes */
    uint8_t flags; /**< TCP flags */
    uint16_t window_size; /**< Window size */
    uint16_t checksum; /**< Checksum */
    uint16_t urgent_pointer; /**< Urgent pointer */
} tcp_header_t;

/**
 * @brief Parses raw bytes into a TCP header structure.
 *
 * @param buffer Pointer to the raw packet bytes.
 * @param packet_size Total available size of the packet.
 * @param header Pointer to the destination tcp_header_t structure.
 * @return true if successfully parsed, false otherwise.
 */
bool parse_tcp(const uint8_t *buffer, size_t packet_size, tcp_header_t *header);

/**
 * @brief Prints parsed TCP header details to standard output.
 *
 * @param header Pointer to the parsed tcp_header_t structure.
 */
void print_tcp(const tcp_header_t *header);

#endif /* TCP_H */