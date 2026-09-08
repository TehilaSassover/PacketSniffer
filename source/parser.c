#include <stdio.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "../header/parser.h"
#include "layer_2/ethernet.h"
#include "layer_2/arp.h"
#include "layer_2/vlan.h"
#include "layer_3/ipv4.h"
#include "layer_3/ipv6.h"
#include "layer_3/icmp.h"
#include "layer_3/icmpv6.h"
#include "layer_4/tcp.h"
#include "layer_4/udp.h"

/* Layer 7 Includes */
#include "layer_5-7/http.h"
#include "layer_5-7/https.h"
#include "layer_5-7/dns.h"
#include "layer_5-7/dhcp.h"
#include "layer_5-7/ftp.h"
#include "layer_5-7/ssh.h"
#include "layer_5-7/ntp.h"
#include "layer_5-7/telnet.h"

static int packet_counter = 1;

void dispatch_tcp_app(uint16_t src_port, uint16_t dst_port, const uint8_t *payload, size_t payload_size)
{
    if (payload == NULL || payload_size == 0)
    {
        return;
    }

    if (src_port == PORT_HTTP || dst_port == PORT_HTTP)
    {
        http_info_t http_info;
        if (parse_http(payload, payload_size, &http_info))
        {
            print_http(&http_info, payload, payload_size);
        }
    }
    else if (src_port == PORT_HTTPS || dst_port == PORT_HTTPS)
    {
        https_info_t https_info;
        if (parse_https(payload, payload_size, &https_info))
        {
            print_https(&https_info, payload, payload_size);
        }
    }
    else if (src_port == PORT_FTP_CTRL || dst_port == PORT_FTP_CTRL ||
             src_port == PORT_FTP_DATA || dst_port == PORT_FTP_DATA)
    {
        ftp_info_t ftp_info;
        if (parse_ftp(payload, payload_size, &ftp_info))
        {
            print_ftp(&ftp_info, payload, payload_size);
        }
    }
    else if (src_port == PORT_SSH || dst_port == PORT_SSH)
    {
        ssh_info_t ssh_info;
        if (parse_ssh(payload, payload_size, &ssh_info))
        {
            print_ssh(&ssh_info, payload, payload_size);
        }
    }
    else if (src_port == PORT_TELNET || dst_port == PORT_TELNET)
    {
        telnet_info_t telnet_info;
        if (parse_telnet(payload, payload_size, &telnet_info))
        {
            print_telnet(&telnet_info, payload, payload_size);
        }
    }
    else if (src_port == PORT_DNS || dst_port == PORT_DNS)
    {
        dns_info_t dns_info;
        if (parse_dns(payload, payload_size, &dns_info))
        {
            print_dns(&dns_info, payload, payload_size);
        }
    }
}

void dispatch_udp_app(uint16_t src_port, uint16_t dst_port, const uint8_t *payload, size_t payload_size)
{
    if (payload == NULL || payload_size == 0)
    {
        return;
    }

    if (src_port == PORT_DNS || dst_port == PORT_DNS)
    {
        dns_info_t dns_info;
        if (parse_dns(payload, payload_size, &dns_info))
        {
            print_dns(&dns_info, payload, payload_size);
        }
    }
    else if (src_port == PORT_DHCP_SER || dst_port == PORT_DHCP_SER ||
             src_port == PORT_DHCP_CLI || dst_port == PORT_DHCP_CLI)
    {
        dhcp_info_t dhcp_info;
        if (parse_dhcp(payload, payload_size, &dhcp_info))
        {
            print_dhcp(&dhcp_info, payload, payload_size);
        }
    }
    else if (src_port == PORT_NTP || dst_port == PORT_NTP)
    {
        ntp_info_t ntp_info;
        if (parse_ntp(payload, payload_size, &ntp_info))
        {
            print_ntp(&ntp_info, payload, payload_size);
        }
    }
}

bool process_layer4_payload(uint8_t protocol, const uint8_t *payload, size_t payload_size)
{
    if (protocol == IPPROTO_ICMP)
    {
        icmp_header_t icmp_header;
        if (!parse_icmp(payload, payload_size, &icmp_header))
        {
            printf("Failed to parse ICMP packet\n");
            return false;
        }
        print_icmp(&icmp_header);
    }
    else if (protocol == IPPROTO_ICMPV6)
    {
        icmpv6_header_t icmpv6_header;
        if (!parse_icmpv6(payload, payload_size, &icmpv6_header))
        {
            printf("Failed to parse ICMPv6 packet\n");
            return false;
        }
        print_icmpv6(&icmpv6_header);
    }
    else if (protocol == IPPROTO_TCP)
    {
        tcp_header_t tcp_header;
        if (!parse_tcp(payload, payload_size, &tcp_header))
        {
            printf("Failed to parse TCP packet\n");
            return false;
        }
        print_tcp(&tcp_header);

        size_t tcp_header_bytes = tcp_header.data_offset;
        if (payload_size > tcp_header_bytes)
        {
            const uint8_t *l7_payload = payload + tcp_header_bytes;
            size_t l7_payload_size = payload_size - tcp_header_bytes;
            dispatch_tcp_app(tcp_header.src_port, tcp_header.dst_port, l7_payload, l7_payload_size);
        }
    }
    else if (protocol == IPPROTO_UDP)
    {
        udp_header_t udp_header;
        if (!parse_udp(payload, payload_size, &udp_header))
        {
            printf("Failed to parse UDP packet\n");
            return false;
        }
        print_udp(&udp_header);

        if (payload_size > UDP_HEADER_SIZE)
        {
            const uint8_t *l7_payload = payload + UDP_HEADER_SIZE;
            size_t l7_payload_size = payload_size - UDP_HEADER_SIZE;
            dispatch_udp_app(udp_header.src_port, udp_header.dst_port, l7_payload, l7_payload_size);
        }
    }

    return true;
}

bool dispatch_protocol(uint16_t ether_type, const uint8_t *payload, size_t payload_size)
{
    switch (ether_type)
    {
    case ETHERTYPE_ARP:
    {
        arp_header_t arp_header;
        if (!parse_arp(payload, payload_size, &arp_header))
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
        if (!parse_ipv4(payload, payload_size, &ipv4_header))
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

            return process_layer4_payload(ipv4_header.protocol, l4_payload, l4_payload_size);
        }
        return true;
    }

    case ETHERTYPE_IPV6:
    {
        ipv6_header_t ipv6_header;
        if (!parse_ipv6(payload, payload_size, &ipv6_header))
        {
            printf("Failed to parse IPv6 packet\n");
            return false;
        }
        print_ipv6_header(&ipv6_header);

        if (payload_size > IPV6_HEADER_SIZE)
        {
            const uint8_t *l4_payload = payload + IPV6_HEADER_SIZE;
            size_t l4_payload_size = payload_size - IPV6_HEADER_SIZE;

            return process_layer4_payload(ipv6_header.next_header, l4_payload, l4_payload_size);
        }
        return true;
    }

    case ETHERTYPE_VLAN:
    {
        vlan_header_t vlan_header;
        if (!parse_vlan(payload, payload_size, &vlan_header))
        {
            printf("Failed to parse VLAN packet\n");
            return false;
        }
        print_vlan(&vlan_header);

        const uint8_t *inner_payload = payload + VLAN_HEADER_SIZE;
        size_t inner_payload_size = payload_size - VLAN_HEADER_SIZE;

        return dispatch_protocol(vlan_header.inner_ether_type, inner_payload, inner_payload_size);
    }

    default:
        printf("Unsupported EtherType: 0x%04X\n", ether_type);
        return true;
    }
}

bool parse_packet(const uint8_t *buffer, size_t packet_size)
{
    ethernet_header_t ethernet_header;

    if (!parse_ethernet(buffer, packet_size, &ethernet_header))
    {
        printf("Failed to parse Ethernet packet\n");
        return false;
    }

    printf("====================================================\n");
    printf("Packet #%d\n", packet_counter++);

    print_ethernet(&ethernet_header);

    const uint8_t *payload = buffer + ETHERNET_II_HEADER_SIZE;
    size_t payload_size = packet_size - ETHERNET_II_HEADER_SIZE;

    return dispatch_protocol(ethernet_header.ether_type, payload, payload_size);
}