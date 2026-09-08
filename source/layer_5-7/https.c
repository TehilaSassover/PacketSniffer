#include <stdio.h>
#include <string.h>

#include "../../header/layer_5-7/https.h"
#include "../../header/utils.h"


bool parse_https(const uint8_t *buffer, size_t size, https_info_t *info)
{
    if (buffer == NULL || size < TLS_HEADER_SIZE || info == NULL)
    {
        return false;
    }

    info->content_type = buffer[TLS_OFFSET_CONTENT_TYPE];
    info->version      = read_uint16_be(buffer + TLS_OFFSET_VERSION);
    info->length       = read_uint16_be(buffer + TLS_OFFSET_LENGTH);

    return true;
}

void print_https(const https_info_t *info, const uint8_t *payload, size_t payload_size)
{
    if (info == NULL)
    {
        return;
    }

    printf("Layer 5-7\n");
    printf("----------\n");
    printf("Protocol     : HTTPS (TLS)\n");
    printf("Content Type : 0x%02X\n", info->content_type);
    printf("TLS Version  : 0x%04X\n", info->version);
    printf("Record Length: %u bytes\n", info->length);

    print_payload(payload, payload_size);
}