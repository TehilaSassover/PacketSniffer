#ifndef ICMP_H
#define ICMP_H

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

/* ICMP Protocol Constants */
#define ICMP_HEADER_MIN_SIZE 8

/* ICMP Message Types */
#define ICMP_TYPE_ECHO_REPLY            0
#define ICMP_TYPE_DEST_UNREACHABLE      3
#define ICMP_TYPE_REDIRECT              5
#define ICMP_TYPE_ECHO_REQUEST          8
#define ICMP_TYPE_TIME_EXCEEDED         11

typedef struct {
    uint8_t  type;
    uint8_t  code;
    uint16_t checksum;
    uint16_t rest_of_header_1;
    uint16_t rest_of_header_2;
} icmp_header_t;

bool parse_icmp(const uint8_t *buffer, size_t packet_size, icmp_header_t *header);
void print_icmp(const icmp_header_t *header);

#endif /* ICMP_H */