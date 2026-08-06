#include <stdio.h>

#include "parser.h"
#include "layer_2/ethernet.h"
#include "layer_2/arp.h"

static bool dispatch_payload(
    uint16_t ether_type,
    const uint8_t *payload,
    size_t payload_size)
{
    switch (ether_type)
    {
    case ETHERTYPE_ARP:
    {
        arp_header_t arp_header;

        if (!parse_arp(
                payload,
                payload_size,
                &arp_header))
        {
            printf("Failed to parse ARP packet\n");
            return false;
        }

        print_arp(&arp_header);

        return true;
    }

    case ETHERTYPE_IPV4:
        printf("IPv4 parsing is not implemented yet\n");
        return true;

    case ETHERTYPE_IPV6:
        printf("IPv6 parsing is not implemented yet\n");
        return true;

    case ETHERTYPE_VLAN:
        printf("VLAN parsing is not implemented yet\n");
        return true;

    default:
        printf(
            "Unsupported EtherType: 0x%04X\n",
            ether_type);

        return true;
    }
}

bool parse_packet(
    const uint8_t *buffer,
    size_t packet_size)
{
    ethernet_header_t ethernet_header;

    if (!parse_ethernet(
            buffer,
            packet_size,
            &ethernet_header))
    {
        printf("Failed to parse Ethernet packet\n");
        return false;
    }

    print_ethernet(&ethernet_header);

    const uint8_t *payload =
        buffer + ETHERNET_II_HEADER_SIZE;

    size_t payload_size =
        packet_size - ETHERNET_II_HEADER_SIZE;

    return dispatch_payload(
        ethernet_header.ether_type,
        payload,
        payload_size);
}