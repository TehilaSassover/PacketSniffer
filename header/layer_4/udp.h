#ifndef UDP_H
#define UDP_H

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#define UDP_HEADER_SIZE 8

typedef struct {
    uint16_t src_port;
    uint16_t dst_port;
    uint16_t length;
    uint16_t checksum;
} udp_header_t;

bool parse_udp(const uint8_t *buffer, size_t packet_size, udp_header_t *header);
void print_udp(const udp_header_t *header);

#endif /* UDP_H */