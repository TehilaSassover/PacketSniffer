#ifndef PARSER_H
#define PARSER_H

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

/**
 * @file parser.h
 * @brief Packet parser module for dispatching network layers.
 */

/* Layer 3 Protocol Numbers */
#ifndef IPPROTO_ICMP
#define IPPROTO_ICMP 1
#endif

#ifndef IPPROTO_TCP
#define IPPROTO_TCP 6
#endif

#ifndef IPPROTO_UDP
#define IPPROTO_UDP 17
#endif

#ifndef IPPROTO_ICMPV6
#define IPPROTO_ICMPV6 58
#endif

/* Layer 4 / 7 Port Definitions */
#define PORT_FTP_DATA  20
#define PORT_FTP_CTRL  21
#define PORT_SSH       22
#define PORT_TELNET    23
#define PORT_DNS       53
#define PORT_DHCP_SER  67
#define PORT_DHCP_CLI  68
#define PORT_HTTP      80
#define PORT_NTP       123
#define PORT_HTTPS     443

/* Protocol Header Sizes */
#define IPV6_HEADER_SIZE 40
#define UDP_HEADER_SIZE  8

/**
 * @brief Dispatch Layer 7 application protocols based on TCP ports.
 *
 * @param src_port Source port number.
 * @param dst_port Destination port number.
 * @param payload Pointer to the L7 payload data.
 * @param payload_size Size of the L7 payload.
 */
void dispatch_tcp_app(uint16_t src_port, uint16_t dst_port, const uint8_t *payload, size_t payload_size);

/**
 * @brief Dispatch Layer 7 application protocols based on UDP ports.
 *
 * @param src_port Source port number.
 * @param dst_port Destination port number.
 * @param payload Pointer to the L7 payload data.
 * @param payload_size Size of the L7 payload.
 */
void dispatch_udp_app(uint16_t src_port, uint16_t dst_port, const uint8_t *payload, size_t payload_size);

/**
 * @brief Process Layer 4 protocol payload (TCP, UDP, ICMP).
 *
 * @param protocol Next header / protocol ID.
 * @param payload Pointer to the L4 header/payload buffer.
 * @param payload_size Size of the L4 buffer.
 * @return true if L4 layer was parsed successfully, false otherwise.
 */
bool process_layer4_payload(uint8_t protocol, const uint8_t *payload, size_t payload_size);

/**
 * @brief Dispatch payload based on EtherType value.
 *
 * @param ether_type The Ethernet protocol type.
 * @param payload Pointer to the layer payload buffer.
 * @param payload_size Size of the layer payload buffer.
 * @return true if handled successfully, false on parsing failure.
 */
bool dispatch_protocol(uint16_t ether_type, const uint8_t *payload, size_t payload_size);

/**
 * @brief Parses an incoming network packet starting from Layer 2.
 *
 * @param buffer Pointer to the raw packet bytes.
 * @param packet_size Total length of the raw packet.
 * @return true if the packet was successfully parsed, false otherwise.
 */
bool parse_packet(const uint8_t *buffer, size_t packet_size);

#endif /* PARSER_H */