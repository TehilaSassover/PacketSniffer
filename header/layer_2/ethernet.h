#ifndef ETHERNET_H
#define ETHERNET_H

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#define MAC_ADDRESS_SIZE 6

#define ETHERNET_II_HEADER_SIZE 14

#define ETHERNET_DESTINATION_MAC_OFFSET 0
#define ETHERNET_SOURCE_MAC_OFFSET      6
#define ETHERNET_ETHERTYPE_OFFSET       12

#define ETHERTYPE_IPV4 0x0800
#define ETHERTYPE_ARP  0x0806
#define ETHERTYPE_IPV6 0x86DD
#define ETHERTYPE_VLAN 0x8100


typedef struct ethernet_header
{
    uint8_t destination_mac[MAC_ADDRESS_SIZE];
    uint8_t source_mac[MAC_ADDRESS_SIZE];

    uint16_t ether_type;

} ethernet_header_t;


bool parse_ethernet(
    const uint8_t *buffer,
    size_t packet_size,
    ethernet_header_t *header
);


void print_ethernet(
    const ethernet_header_t *header
);

#endif