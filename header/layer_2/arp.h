#ifndef ARP_H
#define ARP_H

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#define ARP_FIXED_HEADER_SIZE 8

#define ARP_HARDWARE_TYPE_OFFSET            0
#define ARP_PROTOCOL_TYPE_OFFSET            2
#define ARP_HARDWARE_ADDRESS_LENGTH_OFFSET  4
#define ARP_PROTOCOL_ADDRESS_LENGTH_OFFSET  5
#define ARP_OPERATION_OFFSET                6

#define ARP_HARDWARE_TYPE_ETHERNET 0x0001
#define ARP_OPERATION_REQUEST 0x0001
#define ARP_OPERATION_REPLY   0x0002


typedef struct arp_header
{
    uint16_t hardware_type;
    uint16_t protocol_type;

    uint8_t hardware_address_length;
    uint8_t protocol_address_length;

    uint16_t operation;

    const uint8_t *sender_hardware_address;
    const uint8_t *sender_protocol_address;

    const uint8_t *target_hardware_address;
    const uint8_t *target_protocol_address;

} arp_header_t;


bool parse_arp(
    const uint8_t *buffer,
    size_t packet_size,
    arp_header_t *header
);


void print_arp(
    const arp_header_t *header
);

#endif