#include <stdio.h>
#include <string.h>

#include "../../header/layer_5-7/dhcp.h"
#include "../../header/utils.h"

bool parse_dhcp(const uint8_t *buffer, size_t size, dhcp_info_t *info)
{
    if (buffer == NULL || size < DHCP_HEADER_MIN_SIZE || info == NULL)
    {
        return false;
    }

    info->op    = buffer[DHCP_OFFSET_OP];
    info->htype = buffer[DHCP_OFFSET_HTYPE];
    info->hlen  = buffer[DHCP_OFFSET_HLEN];
    info->hops  = buffer[DHCP_OFFSET_HOPS];

    info->xid   = read_uint32_be(buffer + DHCP_OFFSET_XID);
    info->secs  = read_uint16_be(buffer + DHCP_OFFSET_SECS);
    info->flags = read_uint16_be(buffer + DHCP_OFFSET_FLAGS);

    info->ciaddr = read_uint32_be(buffer + DHCP_OFFSET_CIADDR);
    info->yiaddr = read_uint32_be(buffer + DHCP_OFFSET_YIADDR);
    info->siaddr = read_uint32_be(buffer + DHCP_OFFSET_SIADDR);
    info->giaddr = read_uint32_be(buffer + DHCP_OFFSET_GIADDR);

    memcpy(info->chaddr, buffer + DHCP_OFFSET_CHADDR, DHCP_CHADDR_LEN);

    info->magic_cookie = read_uint32_be(buffer + DHCP_OFFSET_MAGIC_COOKIE);

    return true;
}

void print_dhcp(const dhcp_info_t *info, const uint8_t *payload, size_t payload_size)
{
    if (info == NULL)
    {
        return;
    }

    printf("Layer 5-7\n");
    printf("----------\n");
    printf("Protocol        : DHCP\n");
    printf("Opcode          : %u\n", info->op);
    printf("Hardware Type   : %u\n", info->htype);
    printf("Hardware Length : %u\n", info->hlen);
    printf("Hops            : %u\n", info->hops);
    printf("Transaction ID  : 0x%08X\n", info->xid);
    printf("Seconds Elapsed : %u\n", info->secs);
    printf("Flags           : 0x%04X\n", info->flags);

    printf("Client IP       : ");
    print_ipv4((const uint8_t *)&info->ciaddr);
    printf("\nYour IP         : ");
    print_ipv4((const uint8_t *)&info->yiaddr);
    printf("\nServer IP       : ");
    print_ipv4((const uint8_t *)&info->siaddr);
    printf("\nGateway IP      : ");
    print_ipv4((const uint8_t *)&info->giaddr);
    
    printf("\nClient MAC      : ");
    print_mac(info->chaddr);
    printf("\nMagic Cookie    : 0x%08X\n", info->magic_cookie);

    print_payload(payload, payload_size);
}