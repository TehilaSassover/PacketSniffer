#include <stdio.h>
#include <string.h>
#include <arpa/inet.h>
#include "layer_4/tcp.h"

bool parse_tcp(const uint8_t *buffer, size_t packet_size, tcp_header_t *header)
{
    if (buffer == NULL || header == NULL || packet_size < TCP_HEADER_MIN_SIZE)
    {
        return false;
    }

    uint16_t raw_src_port, raw_dst_port;
    uint32_t raw_seq_num, raw_ack_num;
    uint16_t raw_window, raw_checksum, raw_urgent;

    memcpy(&raw_src_port, buffer + 0, sizeof(raw_src_port));
    memcpy(&raw_dst_port, buffer + 2, sizeof(raw_dst_port));
    memcpy(&raw_seq_num,  buffer + 4, sizeof(raw_seq_num));
    memcpy(&raw_ack_num,  buffer + 8, sizeof(raw_ack_num));

    header->src_port = ntohs(raw_src_port);
    header->dst_port = ntohs(raw_dst_port);
    header->seq_num  = ntohl(raw_seq_num);
    header->ack_num  = ntohl(raw_ack_num);

    /* 4 הביטים העליונים של בייט 12 הם אורך הכותרת ביחידות של 4 בייטים */
    header->data_offset = (buffer[12] >> 4) * 4;

    /* בדיקה שאורך הכותרת שנרשם תקין ומוכל בגודל ה-Buffer */
    if (header->data_offset < TCP_HEADER_MIN_SIZE || packet_size < header->data_offset)
    {
        return false;
    }

    header->flags = buffer[13];

    memcpy(&raw_window,   buffer + 14, sizeof(raw_window));
    memcpy(&raw_checksum, buffer + 16, sizeof(raw_checksum));
    memcpy(&raw_urgent,   buffer + 18, sizeof(raw_urgent));

    header->window_size    = ntohs(raw_window);
    header->checksum       = ntohs(raw_checksum);
    header->urgent_pointer = ntohs(raw_urgent);

    return true;
}

void print_tcp(const tcp_header_t *header)
{
    if (header == NULL)
    {
        return;
    }

    printf("Layer 4\n");
    printf("--------\n");
    printf("Protocol        : TCP\n");
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