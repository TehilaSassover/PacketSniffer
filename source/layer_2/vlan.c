#include <stdio.h>
#include <string.h>
#include <arpa/inet.h>

#include "layer_2/vlan.h"
#include "utils.h"

bool parse_vlan(
    const uint8_t *buffer,
    size_t packet_size,
    vlan_header_t *header)
{
    if (buffer == NULL ||
        header == NULL ||
        packet_size < VLAN_HEADER_SIZE)
    {
        return false;
    }

    memcpy(
        header,
        buffer,
        sizeof(vlan_header_t));

    header->tci =
        ntohs(header->tci);

    header->inner_ether_type =
        ntohs(header->inner_ether_type);

    return true;
}

uint16_t get_vlan_id(
    const vlan_header_t *header)
{
    return header->tci & VLAN_ID_MASK;
}

uint8_t get_vlan_pcp(
    const vlan_header_t *header)
{
    return (header->tci >> VLAN_PCP_SHIFT) & VLAN_PCP_MASK;
}

uint8_t get_vlan_dei(
    const vlan_header_t *header)
{
    return (header->tci >> VLAN_DEI_SHIFT) & VLAN_DEI_MASK;
}

void print_vlan(
    const vlan_header_t *header)
{
    if (header == NULL)
    {
        return;
    }

    printf("VLAN\n");
    printf("--------\n");

    printf(
        "PCP              : %u\n",
        get_vlan_pcp(header));

    printf(
        "DEI              : %u\n",
        get_vlan_dei(header));

    printf(
        "VLAN ID          : %u\n",
        get_vlan_id(header));

    printf(
        "Inner EtherType  : 0x%04X\n",
        header->inner_ether_type);
}