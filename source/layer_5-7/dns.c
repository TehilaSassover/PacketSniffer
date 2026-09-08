#include <stdio.h>
#include <string.h>

#include "layer_5-7/dns.h"
#include "utils.h"

bool parse_dns(const uint8_t *buffer, size_t size, dns_info_t *info)
{
    if (buffer == NULL || size < DNS_HEADER_SIZE || info == NULL)
    {
        return false;
    }

    info->transaction_id   = read_uint16_be(buffer + DNS_OFFSET_TX_ID);
    info->flags            = read_uint16_be(buffer + DNS_OFFSET_FLAGS);
    info->questions_count  = read_uint16_be(buffer + DNS_OFFSET_QUESTIONS);
    info->answers_count    = read_uint16_be(buffer + DNS_OFFSET_ANSWERS);
    info->authority_count  = read_uint16_be(buffer + DNS_OFFSET_AUTHORITY);
    info->additional_count = read_uint16_be(buffer + DNS_OFFSET_ADDITIONAL);

    return true;
}

void print_dns(const dns_info_t *info, const uint8_t *payload, size_t payload_size)
{
    if (info == NULL)
    {
        return;
    }

    print_layer_header("Layer 5-7", "DNS");

    printf("Transaction ID  : 0x%04X\n", info->transaction_id);
    printf("Flags           : 0x%04X\n", info->flags);
    printf("Questions Count : %u\n", info->questions_count);
    printf("Answers Count   : %u\n", info->answers_count);
    printf("Authority Count : %u\n", info->authority_count);
    printf("Additional Count: %u\n", info->additional_count);

    if (payload != NULL && payload_size > 0)
    {
        print_payload(payload, payload_size);
    }
}