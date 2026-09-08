#include <stdio.h>
#include <string.h>
#include <arpa/inet.h>
#include "layer_4/tcp.h"
#include "utils.h"

bool parse_tcp(const uint8_t *buffer, size_t packet_size, tcp_header_t *header)
{
    if (buffer == NULL || header == NULL)
    {
        printf("Error: Null buffer or header provided to TCP parser\n");
        return false;
    }

    if (packet_size < TCP_HEADER_MIN_SIZE)
    {
        printf("Error: Truncated TCP Packet (Size: %zu bytes, Minimum required: %d bytes)\n", 
               packet_size, TCP_HEADER_MIN_SIZE);
        return false;
    }

    header->src_port = read_uint16_be(buffer + 0);
    header->dst_port = read_uint16_be(buffer + 2);
    header->seq_num  = read_uint32_be(buffer + 4);
    header->ack_num  = read_uint32_be(buffer + 8);

    header->data_offset = (buffer[12] >> 4) * 4;

    if (header->data_offset < TCP_HEADER_MIN_SIZE)
    {
        printf("Error: Invalid TCP Data Offset (%u bytes, Minimum required: %d bytes)\n", 
               header->data_offset, TCP_HEADER_MIN_SIZE);
        return false;
    }

    if (packet_size < header->data_offset)
    {
        printf("Error: Incomplete TCP Header (Size: %zu bytes, Header Offset requires: %u bytes)\n", 
               packet_size, header->data_offset);
        return false;
    }

    header->flags           = buffer[13];
    header->window_size     = read_uint16_be(buffer + 14);
    header->checksum        = read_uint16_be(buffer + 16);
    header->urgent_pointer  = read_uint16_be(buffer + 18);

    return true;
}

void print_tcp(const tcp_header_t *header)
{
    if (header == NULL) 
    {
        return;
    }

    print_layer_header("Layer 4", "TCP");

    printf("Source Port     : %u\n", header->src_port);
    printf("Destination Port: %u\n", header->dst_port);
    printf("Sequence Number : %u (0x%08X)\n", header->seq_num, header->seq_num);
    printf("ACK Number      : %u (0x%08X)\n", header->ack_num, header->ack_num);
    printf("Header Length   : %u bytes\n", header->data_offset);
    printf("Flags           : 0x%02X [ ", header->flags);

    if (header->flags & TCP_FLAG_SYN) printf("SYN ");
    if (header->flags & TCP_FLAG_ACK) printf("ACK ");
    if (header->flags & TCP_FLAG_FIN) printf("FIN ");
    if (header->flags & TCP_FLAG_RST) printf("RST ");
    if (header->flags & TCP_FLAG_PSH) printf("PSH ");
    if (header->flags & TCP_FLAG_URG) printf("URG ");

    printf("]\n");
    printf("Window Size     : %u\n", header->window_size);
    printf("Checksum        : 0x%04X\n", header->checksum);
}