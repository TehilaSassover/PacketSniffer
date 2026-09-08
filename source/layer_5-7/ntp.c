#include <stdio.h>
#include <string.h>

#include "../../header/layer_5-7/ntp.h"
#include "../../header/utils.h"

bool parse_ntp(const uint8_t *buffer, size_t size, ntp_info_t *info)
{
    if (buffer == NULL || size < NTP_HEADER_SIZE || info == NULL)
    {
        return false;
    }

    uint8_t first_byte = buffer[NTP_OFFSET_FLAGS];

    info->leap_indicator = (first_byte & NTP_LI_MASK) >> NTP_LI_SHIFT;
    info->version        = (first_byte & NTP_VN_MASK) >> NTP_VN_SHIFT;
    info->mode           = (first_byte & NTP_MODE_MASK);

    info->stratum   = buffer[NTP_OFFSET_STRATUM];
    info->poll      = buffer[NTP_OFFSET_POLL];
    info->precision = (int8_t)buffer[NTP_OFFSET_PRECISION];

    info->ref_id = read_uint32_be(buffer + NTP_OFFSET_REF_ID);

    return true;
}

void print_ntp(const ntp_info_t *info, const uint8_t *payload, size_t payload_size)
{
    if (info == NULL)
    {
        return;
    }

    printf("Layer 5-7\n");
    printf("----------\n");
    printf("Protocol       : NTP\n");
    printf("Version        : %u\n", info->version);
    printf("Mode           : %u\n", info->mode);
    printf("Leap Indicator : %u\n", info->leap_indicator);
    printf("Stratum        : %u\n", info->stratum);
    printf("Poll Interval  : %u\n", info->poll);
    printf("Precision      : %d\n", info->precision);
    printf("Reference ID   : 0x%08X\n", info->ref_id);

    print_payload(payload, payload_size);
}