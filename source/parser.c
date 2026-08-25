#include <stdio.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "parser.h"
#include "layer_2/ethernet.h"
#include "layer_2/arp.h"
#include "layer_2/vlan.h"
#include "layer_3/ipv4.h"
#include "layer_3/ipv6.h"
#include "layer_3/icmp.h"
#include "layer_3/icmpv6.h"
#include "layer_4/tcp.h" /* 1. הוספת Include ל-TCP */

#ifndef IPPROTO_ICMP
#define IPPROTO_ICMP 1
#endif

#ifndef IPPROTO_TCP
#define IPPROTO_TCP 6 /* הוספת הגדרה ל-TCP Protocol ID */
#endif

#ifndef IPPROTO_ICMPV6
#define IPPROTO_ICMPV6 58
#endif

static bool dispatch_protocol(
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
    {
        ipv4_header_t ipv4_header;

        if (!parse_ipv4(
                payload,
                payload_size,
                &ipv4_header))
        {
            printf("Failed to parse IPv4 packet\n");
            return false;
        }

        print_ipv4_header(&ipv4_header);

        size_t ip_header_bytes = ipv4_header.header_length;

        if (payload_size > ip_header_bytes)
        {
            const uint8_t *l4_payload = payload + ip_header_bytes;
            size_t l4_payload_size = payload_size - ip_header_bytes;

            if (ipv4_header.protocol == IPPROTO_ICMP)
            {
                icmp_header_t icmp_header;

                if (!parse_icmp(l4_payload, l4_payload_size, &icmp_header))
                {
                    printf("Failed to parse ICMP packet\n");
                    return false;
                }

                print_icmp(&icmp_header);
            }
            /* 2. תמיכה ב-TCP מעל IPv4 */
            else if (ipv4_header.protocol == IPPROTO_TCP)
            {
                tcp_header_t tcp_header;

                if (!parse_tcp(l4_payload, l4_payload_size, &tcp_header))
                {
                    printf("Failed to parse TCP packet\n");
                    return false;
                }

                print_tcp(&tcp_header);
            }
        }

        return true;
    }

    case ETHERTYPE_IPV6:
    {
        ipv6_header_t ipv6_header;

        if (!parse_ipv6(
                payload,
                payload_size,
                &ipv6_header))
        {
            printf("Failed to parse IPv6 packet\n");
            return false;
        }

        print_ipv6_header(&ipv6_header);

        size_t ipv6_header_bytes = 40; // IPv6 header fixed size

        if (payload_size > ipv6_header_bytes)
        {
            const uint8_t *l4_payload = payload + ipv6_header_bytes;
            size_t l4_payload_size = payload_size - ipv6_header_bytes;

            if (ipv6_header.next_header == IPPROTO_ICMPV6)
            {
                icmpv6_header_t icmpv6_header;

                if (!parse_icmpv6(l4_payload, l4_payload_size, &icmpv6_header))
                {
                    printf("Failed to parse ICMPv6 packet\n");
                    return false;
                }

                print_icmpv6(&icmpv6_header);
            }
            /* 3. תמיכה ב-TCP מעל IPv6 */
            else if (ipv6_header.next_header == IPPROTO_TCP)
            {
                tcp_header_t tcp_header;

                if (!parse_tcp(l4_payload, l4_payload_size, &tcp_header))
                {
                    printf("Failed to parse TCP packet\n");
                    return false;
                }

                print_tcp(&tcp_header);
            }
        }

        return true;
    }

    case ETHERTYPE_VLAN:
    {
        vlan_header_t vlan_header;

        if (!parse_vlan(
                payload,
                payload_size,
                &vlan_header))
        {
            printf("Failed to parse VLAN packet\n");
            return false;
        }

        print_vlan(&vlan_header);

        const uint8_t *inner_payload =
            payload + VLAN_HEADER_SIZE;

        size_t inner_payload_size =
            payload_size - VLAN_HEADER_SIZE;

        return dispatch_protocol(
            vlan_header.inner_ether_type,
            inner_payload,
            inner_payload_size);
    }

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

    return dispatch_protocol(
        ethernet_header.ether_type,
        payload,
        payload_size);
}