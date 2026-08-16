#include <stdint.h>
#include <stddef.h>

#include "parser.h"

int main(void)
{
    // const uint8_t packet[] =
    //     {
    //         0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    //         0x00, 0x15, 0x5D, 0xC3, 0x5C, 0xD4,
    //         0x08, 0x06,

    //         0x00, 0x01,
    //         0x08, 0x00,
    //         0x06,
    //         0x04,
    //         0x00, 0x01,

    //         0x00, 0x15, 0x5D, 0xC3, 0x5C, 0xD4,
    //         0xAC, 0x1F, 0x71, 0x1C,

    //         0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    //         0xAC, 0x1F, 0x70, 0x01};

    // const uint8_t vlan_packet[] =
    //     {
    //         /* Ethernet */
    //         0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    //         0x00, 0x15, 0x5D, 0xC3, 0x5C, 0xD4,

    //         /* EtherType = VLAN (802.1Q) */
    //         0x81, 0x00,

    //         /* VLAN TCI
    //          * PCP = 0
    //          * DEI = 0
    //          * VLAN ID = 100
    //          */
    //         0x00, 0x64,

    //         /* Inner EtherType = IPv4 */
    //         0x08, 0x00};

    // const uint8_t ipv4_packet[] =
    //     {
    //         /* Ethernet */
    //         0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    //         0x00, 0x15, 0x5D, 0xC3, 0x5C, 0xD4,

    //         /* EtherType = IPv4 */
    //         0x08, 0x00,

    //         /* IPv4 Header */

    //         /* Version = 4, IHL = 5 (20 bytes) */
    //         0x45,

    //         /* DSCP = 0, ECN = 0 */
    //         0x00,

    //         /* Total Length = 20 bytes */
    //         0x00, 0x14,

    //         /* Identification = 1 */
    //         0x00, 0x01,

    //         /* Flags = 0, Fragment Offset = 0 */
    //         0x00, 0x00,

    //         /* TTL = 64 */
    //         0x40,

    //         /* Protocol = ICMP */
    //         0x01,

    //         /* Header Checksum */
    //         0x00, 0x00,

    //         /* Source IP = 192.168.1.10 */
    //         0xC0, 0xA8, 0x01, 0x0A,

    //         /* Destination IP = 192.168.1.1 */
    //         0xC0, 0xA8, 0x01, 0x01};

    const uint8_t ipv6_packet[] =
        {
            /* Ethernet */
            0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
            0x00, 0x15, 0x5D, 0xC3, 0x5C, 0xD4,

            /* EtherType = IPv6 */
            0x86, 0xDD,

            /* IPv6 Header */
            /* Version = 6
               Traffic Class = 0
               Flow Label = 0 */
            0x60, 0x00, 0x00, 0x00,

            /* Payload Length = 0 */
            0x00, 0x00,

            /* Next Header = TCP */
            0x06,

            /* Hop Limit = 64 */
            0x40,

            /* Source Address = 2001:db8::1 */
            0x20, 0x01, 0x0D, 0xB8,
            0x00, 0x00, 0x00, 0x00,
            0x00, 0x00, 0x00, 0x00,
            0x00, 0x00, 0x00, 0x01,

            /* Destination Address = 2001:db8::2 */
            0x20, 0x01, 0x0D, 0xB8,
            0x00, 0x00, 0x00, 0x00,
            0x00, 0x00, 0x00, 0x00,
            0x00, 0x00, 0x00, 0x02};

    parse_packet(
        ipv6_packet,
        sizeof(ipv6_packet));

    return 0;
}