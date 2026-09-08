#ifndef ETHERNET_H
#define ETHERNET_H

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

/**
 * @file ethernet.h
 * @brief Ethernet II parser and printer module.
 */

#define MAC_ADDRESS_SIZE 6
#define ETHERNET_II_HEADER_SIZE 14
#define ETHERNET_DESTINATION_MAC_OFFSET 0
#define ETHERNET_SOURCE_MAC_OFFSET 6
#define ETHERNET_ETHERTYPE_OFFSET 12

#define ETHERTYPE_IPV4 0x0800
#define ETHERTYPE_ARP 0x0806
#define ETHERTYPE_IPV6 0x86DD
#define ETHERTYPE_VLAN 0x8100

/**
 * @brief Represents a parsed Ethernet II header structure.
 */
typedef struct ethernet_header
{
    uint8_t destination_mac[MAC_ADDRESS_SIZE]; /**< Destination MAC address */
    uint8_t source_mac[MAC_ADDRESS_SIZE]; /**< Source MAC address */
    uint16_t ether_type; /**< EtherType or length field */
} ethernet_header_t;

/**
 * @brief Parses raw bytes into an Ethernet II header structure.
 *
 * @param buffer Pointer to the raw packet bytes.
 * @param packet_size Total available size of the packet.
 * @param header Pointer to the destination ethernet_header_t structure.
 * @return true if successfully parsed, false otherwise.
 */
bool parse_ethernet(
    const uint8_t *buffer,
    size_t packet_size,
    ethernet_header_t *header
);

/**
 * @brief Prints parsed Ethernet II header details to standard output.
 *
 * @param header Pointer to the parsed ethernet_header_t structure.
 */
void print_ethernet(
    const ethernet_header_t *header
);

#endif /* ETHERNET_H */