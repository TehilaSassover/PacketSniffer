#include <stdio.h>
#include <string.h>
#include <arpa/inet.h>

#include "layer_2/vlan.h"

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

    uint16_t raw_tci;
    uint16_t raw_ethertype;

    memcpy(
        &raw_tci,
        buffer + VLAN_TCI_OFFSET,
        sizeof(raw_tci));

    memcpy(
        &raw_ethertype,
        buffer + VLAN_ETHERTYPE_OFFSET,
        sizeof(raw_ethertype));

    uint16_t tci = ntohs(raw_tci);

    header->pcp =
        (tci >> VLAN_PCP_SHIFT) & VLAN_PCP_MASK;

    header->dei =
        (tci >> VLAN_DEI_SHIFT) & VLAN_DEI_MASK;

    header->vlan_id =
        tci & VLAN_ID_MASK;

    header->inner_ether_type =
        ntohs(raw_ethertype);

    return true;
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

    printf("PCP              : %u\n", header->pcp);
    printf("DEI              : %u\n", header->dei);
    printf("VLAN ID          : %u\n", header->vlan_id);
    printf(
        "Inner EtherType  : 0x%04X\n",
        header->inner_ether_type);
}