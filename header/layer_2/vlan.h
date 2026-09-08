#ifndef VLAN_H
#define VLAN_H

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

/**
 * @file vlan.h
 * @brief VLAN 802.1Q parser and printer module.
 */

#define VLAN_HEADER_SIZE 4

#define VLAN_TCI_OFFSET 0
#define VLAN_ETHERTYPE_OFFSET 2

#define VLAN_PCP_SHIFT 13
#define VLAN_DEI_SHIFT 12

#define VLAN_PCP_MASK 0x07
#define VLAN_DEI_MASK 0x01
#define VLAN_ID_MASK 0x0FFF

/**
 * @brief Represents a parsed VLAN 802.1Q header structure.
 */
typedef struct vlan_header
{
    uint16_t vlan_id; /**< VLAN Identifier (12 bits) */
    uint8_t dei; /**< Drop Eligible Indicator (1 bit) */
    uint8_t pcp; /**< Priority Code Point (3 bits) */
    uint16_t inner_ether_type; /**< Inner encapsulated EtherType */
} vlan_header_t;

/**
 * @brief Parses raw bytes into a VLAN header structure.
 *
 * @param buffer Pointer to the raw packet bytes.
 * @param packet_size Total available size of the packet.
 * @param header Pointer to the destination vlan_header_t structure.
 * @return true if successfully parsed, false otherwise.
 */
bool parse_vlan(
    const uint8_t *buffer,
    size_t packet_size,
    vlan_header_t *header
);

/**
 * @brief Prints parsed VLAN header details to standard output.
 *
 * @param header Pointer to the parsed vlan_header_t structure.
 */
void print_vlan(
    const vlan_header_t *header
);

#endif /* VLAN_H */