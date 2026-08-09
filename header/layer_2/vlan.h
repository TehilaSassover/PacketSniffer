#ifndef VLAN_H
#define VLAN_H

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#define VLAN_HEADER_SIZE 4

#define VLAN_TCI_OFFSET 0
#define VLAN_ETHERTYPE_OFFSET 2

#define VLAN_PCP_SHIFT 13
#define VLAN_DEI_SHIFT 12

#define VLAN_PCP_MASK 0x07
#define VLAN_DEI_MASK 0x01
#define VLAN_ID_MASK 0x0FFF

typedef struct
{
    uint16_t tci;
    uint16_t inner_ether_type;

} vlan_header_t;

bool parse_vlan(
    const uint8_t *buffer,
    size_t packet_size,
    vlan_header_t *header);

uint8_t get_vlan_pcp(
    const vlan_header_t *header);

uint8_t get_vlan_dei(
    const vlan_header_t *header);

uint16_t get_vlan_id(
    const vlan_header_t *header);

void print_vlan(
    const vlan_header_t *header);

#endif