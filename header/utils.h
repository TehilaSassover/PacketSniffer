#ifndef UTILS_H
#define UTILS_H

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

/**
 * @file utils.h
 * @brief Utility and helper functions for packet parsing and printing.
 */

/* Constants */
#define MAC_ADDRESS_SIZE 6
#define UINT64_HIGH_OFFSET 4
#define PRINTABLE_ASCII_MIN 32
#define PRINTABLE_ASCII_MAX 126

/**
 * @brief Prints a MAC address in standard colon-separated hex format.
 *
 * @param mac Pointer to the 6-byte MAC address array.
 */
void print_mac(const unsigned char *mac);

/**
 * @brief Prints an IPv4 address in dot-decimal notation.
 *
 * @param ip Pointer to the 4-byte IPv4 address array.
 */
void print_ipv4(const uint8_t *ip);

/**
 * @brief Reads a 16-bit integer from network byte order and converts to host byte order.
 *
 * @param buffer Pointer to the source buffer.
 * @return uint16_t The converted value.
 */
uint16_t read_uint16_be(const uint8_t *buffer);

/**
 * @brief Reads a 32-bit integer from network byte order and converts to host byte order.
 *
 * @param buffer Pointer to the source buffer.
 * @return uint32_t The converted value.
 */
uint32_t read_uint32_be(const uint8_t *buffer);

/**
 * @brief Reads a 64-bit integer (useful for NTP timestamps) from network byte order.
 *
 * @param buffer Pointer to the source buffer.
 * @return uint64_t The converted 64-bit value.
 */
uint64_t read_uint64_be(const uint8_t *buffer);

/**
 * @brief Prints a buffer of bytes in hexadecimal format separated by spaces.
 *
 * @param buffer Pointer to the data buffer.
 * @param length Number of bytes to print.
 */
void print_bytes_hex(const uint8_t *buffer, size_t length);

/**
 * @brief Prints the payload data as ASCII, replacing non-printable characters with dots.
 *
 * @param payload Pointer to the payload buffer.
 * @param size Size of the payload.
 */
void print_payload(const uint8_t *payload, size_t size);

/**
 * @brief Prints a standard unified header for application layer protocols (Layer 5-7).
 *
 * @param layer_name Name of the layer (e.g., "Layer 5-7").
 * @param protocol_name Name of the protocol (e.g., "HTTP").
 */
void print_layer_header(const char *layer_name, const char *protocol_name);

/**
 * @brief Extracts a single text line from text-based protocols (HTTP, FTP, Telnet).
 *
 * @param buffer Pointer to the input buffer.
 * @param size Available size in the input buffer.
 * @param dest Destination string buffer.
 * @param dest_size Size of the destination buffer.
 * @return size_t Number of bytes extracted.
 */
size_t extract_line(const uint8_t *buffer, size_t size, char *dest, size_t dest_size);

#endif /* UTILS_H */