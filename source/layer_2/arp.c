#include <stdio.h>

#include "layer_2/arp.h"
#include "utils.h"

static const char *get_arp_hardware_type_name(
    uint16_t hardware_type)
{
    switch (hardware_type)
    {
    case ARP_HARDWARE_TYPE_ETHERNET:
        return "Ethernet";

    default:
        return "Unknown";
    }
}

static const char *get_arp_protocol_type_name(
    uint16_t protocol_type)
{
    switch (protocol_type)
    {
    case ARP_PROTOCOL_TYPE_IPV4:
        return "IPv4";

    default:
        return "Unknown";
    }
}

static const char *get_arp_operation_name(
    uint16_t operation)
{
    switch (operation)
    {
    case ARP_OPERATION_REQUEST:
        return "Request";

    case ARP_OPERATION_REPLY:
        return "Reply";

    default:
        return "Unknown";
    }
}

static void print_arp_hardware_address(
    const arp_header_t *header,
    const uint8_t *address)
{
    if (header->hardware_type == ARP_HARDWARE_TYPE_ETHERNET &&
        header->hardware_address_length == MAC_ADDRESS_SIZE)
    {
        print_mac(address);
    }
    else
    {
        print_bytes_hex(
            address,
            header->hardware_address_length);
    }
}

static void print_arp_protocol_address(
    const arp_header_t *header,
    const uint8_t *address)
{
    if (header->protocol_type == ARP_PROTOCOL_TYPE_IPV4 &&
        header->protocol_address_length == IPV4_ADDRESS_SIZE)
    {
        print_ipv4(address);
    }
    else
    {
        print_bytes_hex(
            address,
            header->protocol_address_length);
    }
}

bool parse_arp(
    const uint8_t *buffer,
    size_t packet_size,
    arp_header_t *header)
{
    if (buffer == NULL ||
        header == NULL ||
        packet_size < ARP_FIXED_HEADER_SIZE)
    {
        return false;
    }

    header->hardware_type =
        read_uint16_be(
            buffer + ARP_HARDWARE_TYPE_OFFSET);

    header->protocol_type =
        read_uint16_be(
            buffer + ARP_PROTOCOL_TYPE_OFFSET);

    header->hardware_address_length =
        buffer[ARP_HARDWARE_ADDRESS_LENGTH_OFFSET];

    header->protocol_address_length =
        buffer[ARP_PROTOCOL_ADDRESS_LENGTH_OFFSET];

    header->operation =
        read_uint16_be(
            buffer + ARP_OPERATION_OFFSET);

    size_t required_size =
        ARP_FIXED_HEADER_SIZE + (2 * (size_t)header->hardware_address_length) + (2 * (size_t)header->protocol_address_length);

    if (packet_size < required_size)
    {
        return false;
    }

    size_t offset = ARP_FIXED_HEADER_SIZE;

    header->sender_hardware_address =
        buffer + offset;

    offset += header->hardware_address_length;

    header->sender_protocol_address =
        buffer + offset;

    offset += header->protocol_address_length;

    header->target_hardware_address =
        buffer + offset;

    offset += header->hardware_address_length;

    header->target_protocol_address =
        buffer + offset;

    return true;
}

void print_arp(
    const arp_header_t *header)
{
    if (header == NULL)
    {
        return;
    }

    printf("\nARP\n");
    printf("--------\n");

    printf(
        "Hardware Type    : %s\n",
        get_arp_hardware_type_name(
            header->hardware_type));

    printf(
        "Protocol Type    : %s\n",
        get_arp_protocol_type_name(
            header->protocol_type));

    printf(
        "Hardware Length  : %u\n",
        header->hardware_address_length);

    printf(
        "Protocol Length  : %u\n",
        header->protocol_address_length);

    printf(
        "Operation        : %s\n",
        get_arp_operation_name(
            header->operation));

    printf("Sender MAC       : ");
    print_arp_hardware_address(
        header,
        header->sender_hardware_address);
    printf("\n");

    printf("Sender IP        : ");
    print_arp_protocol_address(
        header,
        header->sender_protocol_address);
    printf("\n");

    printf("Target MAC       : ");
    print_arp_hardware_address(
        header,
        header->target_hardware_address);
    printf("\n");

    printf("Target IP        : ");
    print_arp_protocol_address(
        header,
        header->target_protocol_address);
    printf("\n");
}