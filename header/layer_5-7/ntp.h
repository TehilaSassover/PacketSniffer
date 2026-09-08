#ifndef NTP_H
#define NTP_H

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

/* NTP Constants */
#define NTP_HEADER_SIZE         48

/* NTP Field Offsets */
#define NTP_OFFSET_FLAGS        0
#define NTP_OFFSET_STRATUM      1
#define NTP_OFFSET_POLL         2
#define NTP_OFFSET_PRECISION    3
#define NTP_OFFSET_REF_ID       4
#define NTP_OFFSET_TRANSMIT_TS  40

/* Bitmask Definitions for First Byte */
#define NTP_LI_MASK             0xC0
#define NTP_LI_SHIFT            6
#define NTP_VN_MASK             0x38
#define NTP_VN_SHIFT            3
#define NTP_MODE_MASK           0x07

typedef struct {
    uint8_t leap_indicator;
    uint8_t version;
    uint8_t mode;
    uint8_t stratum;
    uint8_t poll;
    int8_t precision;
    uint32_t ref_id;
} ntp_info_t;

/**
 * @brief Parses NTP packet header.
 * @param buffer Raw packet buffer.
 * @param size Buffer size in bytes (minimum NTP_HEADER_SIZE).
 * @param info Output structure for parsed NTP header.
 * @return true on success, false if buffer is too short.
 */
bool parse_ntp(const uint8_t *buffer, size_t size, ntp_info_t *info);

/**
 * @brief Prints parsed NTP parameters and payload.
 * @param info Parsed NTP structure.
 * @param payload Payload buffer.
 * @param payload_size Payload size in bytes.
 */
void print_ntp(const ntp_info_t *info, const uint8_t *payload, size_t payload_size);

#endif /* NTP_H */