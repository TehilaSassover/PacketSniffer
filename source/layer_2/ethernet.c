#include <stdio.h>
#include <string.h>
#include <arpa/inet.h>
#include <stdint.h>

#include "layer_2/ethernet.h"


static void print_mac(const unsigned char *mac)
{
    for (int i = 0; i < MAC_ADDRESS_SIZE; i++)
    {
        printf("%02X", mac[i]);

        if (i < MAC_ADDRESS_SIZE - 1)
        {
            printf(":");
        }
    }
}


static uint16_t read_ether_type(const unsigned char *buffer)
{
    uint16_t ether_type;

    memcpy(&ether_type,
           buffer + ETHERNET_ETHERTYPE_OFFSET,
           sizeof(ether_type));

    return ntohs(ether_type);
}


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


bool parse_ethernet(const unsigned char *buffer, int packet_size)
{
    if (buffer == NULL || packet_size < ETHERNET_II_HEADER_SIZE)
    {
        printf("Invalid Ethernet packet\n");
        return false;
    }

    uint16_t ether_type = read_ether_type(buffer);

    printf("Layer 2\n");
    printf("--------\n");
    printf("Protocol         : Ethernet II\n");

    printf("Destination MAC  : ");
    print_mac(buffer + ETHERNET_DESTINATION_MAC_OFFSET);
    printf("\n");

    printf("Source MAC       : ");
    print_mac(buffer + ETHERNET_SOURCE_MAC_OFFSET);
    printf("\n");

    printf("EtherType        : 0x%04X (%s)\n",
           ether_type,
           get_ether_type_name(ether_type));

    return true;
}