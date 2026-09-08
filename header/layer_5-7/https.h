#ifndef HTTPS_H
#define HTTPS_H

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

#define TLS_HEADER_SIZE 5

#define TLS_OFFSET_CONTENT_TYPE 0
#define TLS_OFFSET_VERSION      1
#define TLS_OFFSET_LENGTH       3

typedef struct {
    uint8_t content_type;
    uint16_t version;
    uint16_t length;
} https_info_t;

/**
 * @brief Parses TLS record header for HTTPS traffic.
 * @param buffer Raw packet buffer.
 * @param size Buffer size in bytes (minimum TLS_HEADER_SIZE).
 * @param info Output structure for parsed TLS record header.
 * @return true on success, false if buffer is too short.
 */
bool parse_https(const uint8_t *buffer, size_t size, https_info_t *info);

/**
 * @brief Prints parsed HTTPS/TLS record header and encrypted payload.
 * @param info Parsed HTTPS structure.
 * @param payload Payload buffer.
 * @param payload_size Payload size in bytes.
 */
void print_https(const https_info_t *info, const uint8_t *payload, size_t payload_size);

#endif /* HTTPS_H */