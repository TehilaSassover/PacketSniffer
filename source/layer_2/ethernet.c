#include <stdio.h>
#include <string.h>

#include "layer_2/ethernet.h"
#include "utils.h"

static const char *get_ether_type_name(uint16_t ether_type)
{
    switch (ether_type)
    {
    case ETHERTYPE_IPV4:
        return "IPv4";

    case ETHERTYPE_ARP:
        return "ARP";

    case ETHERTYPE_IPV6:
        return "IPv6";

    case ETHERTYPE_VLAN:
        return "VLAN";

    default:
        return "Unknown";
    }
}

bool parse_ethernet(
    const uint8_t *buffer,
    size_t packet_size,
    ethernet_header_t *header)
{
    if (buffer == NULL ||
        header == NULL ||
        packet_size < ETHERNET_II_HEADER_SIZE)
    {
        return false;
    }

    memcpy(
        header->destination_mac,
        buffer + ETHERNET_DESTINATION_MAC_OFFSET,
        MAC_ADDRESS_SIZE);

    memcpy(
        header->source_mac,
        buffer + ETHERNET_SOURCE_MAC_OFFSET,
        MAC_ADDRESS_SIZE);

    header->ether_type =
        read_uint16_be(
            buffer + ETHERNET_ETHERTYPE_OFFSET);

    return true;
}

void print_ethernet(
    const ethernet_header_t *header)
{
    if (header == NULL)
    {
        return;
    }

    printf("Layer 2\n");
    printf("--------\n");

    printf("Protocol         : Ethernet II\n");

    printf("Destination MAC  : ");
    print_mac(header->destination_mac);
    printf("\n");

    printf("Source MAC       : ");
    print_mac(header->source_mac);
    printf("\n");

    printf(
        "EtherType        : 0x%04X (%s)\n",
        header->ether_type,
        get_ether_type_name(header->ether_type));
}