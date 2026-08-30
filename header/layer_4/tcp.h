#ifndef TCP_H
#define TCP_H

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

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

typedef struct {
    uint16_t src_port;
    uint16_t dst_port;
    uint32_t seq_num;
    uint32_t ack_num;
    uint8_t  data_offset; /* אורך הכותרת ב-Words של 32 ביט */
    uint8_t  flags;
    uint16_t window_size;
    uint16_t checksum;
    uint16_t urgent_pointer;
} tcp_header_t;

bool parse_tcp(const uint8_t *buffer, size_t packet_size, tcp_header_t *header);
void print_tcp(const tcp_header_t *header);

#endif /* TCP_H */