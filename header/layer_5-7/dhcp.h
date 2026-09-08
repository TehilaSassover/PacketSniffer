#ifndef DHCP_H
#define DHCP_H

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

/* DHCP Constants */
#define DHCP_HEADER_MIN_SIZE 240
#define DHCP_MAGIC_COOKIE    0x63825363
#define DHCP_CHADDR_LEN      16

/* DHCP Field Offsets */
#define DHCP_OFFSET_OP           0
#define DHCP_OFFSET_HTYPE        1
#define DHCP_OFFSET_HLEN         2
#define DHCP_OFFSET_HOPS         3
#define DHCP_OFFSET_XID          4
#define DHCP_OFFSET_SECS         8
#define DHCP_OFFSET_FLAGS        10
#define DHCP_OFFSET_CIADDR       12
#define DHCP_OFFSET_YIADDR       16
#define DHCP_OFFSET_SIADDR       20
#define DHCP_OFFSET_GIADDR       24
#define DHCP_OFFSET_CHADDR       28
#define DHCP_OFFSET_MAGIC_COOKIE 236

typedef struct {
    uint8_t op;
    uint8_t htype;
    uint8_t hlen;
    uint8_t hops;
    uint32_t xid;
    uint16_t secs;
    uint16_t flags;
    uint32_t ciaddr;
    uint32_t yiaddr;
    uint32_t siaddr;
    uint32_t giaddr;
    uint8_t chaddr[DHCP_CHADDR_LEN];
    uint32_t magic_cookie;
} dhcp_info_t;

/**
 * @brief Parses DHCP fixed header fields.
 * @param buffer Raw packet buffer.
 * @param size Buffer size in bytes (minimum DHCP_HEADER_MIN_SIZE).
 * @param info Output structure for parsed DHCP fields.
 * @return true on success, false if buffer is too short.
 */
bool parse_dhcp(const uint8_t *buffer, size_t size, dhcp_info_t *info);

/**
 * @brief Prints parsed DHCP fields, network addresses, and payload.
 * @param info Parsed DHCP structure.
 * @param payload Payload buffer.
 * @param payload_size Payload size in bytes.
 */
void print_dhcp(const dhcp_info_t *info, const uint8_t *payload, size_t payload_size);

#endif /* DHCP_H */