#ifndef DNS_H
#define DNS_H

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

#define DNS_HEADER_SIZE 12

#define DNS_OFFSET_TX_ID       0
#define DNS_OFFSET_FLAGS       2
#define DNS_OFFSET_QUESTIONS   4
#define DNS_OFFSET_ANSWERS     6
#define DNS_OFFSET_AUTHORITY   8
#define DNS_OFFSET_ADDITIONAL  10

typedef struct {
    uint16_t transaction_id;
    uint16_t flags;
    uint16_t questions_count;
    uint16_t answers_count;
    uint16_t authority_count;
    uint16_t additional_count;
} dns_info_t;

/**
 * @brief Parses DNS packet header.
 * @param buffer Raw packet buffer.
 * @param size Buffer size in bytes (minimum DNS_HEADER_SIZE).
 * @param info Output structure for parsed DNS header fields.
 * @return true on success, false if buffer is too short.
 */
bool parse_dns(const uint8_t *buffer, size_t size, dns_info_t *info);

/**
 * @brief Prints parsed DNS transaction fields and payload.
 * @param info Parsed DNS structure.
 * @param payload Payload buffer.
 * @param payload_size Payload size in bytes.
 */
void print_dns(const dns_info_t *info, const uint8_t *payload, size_t payload_size);

#endif /* DNS_H */