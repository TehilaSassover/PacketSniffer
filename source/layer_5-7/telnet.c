#include <stdio.h>
#include <string.h>

#include "../../header/layer_5-7/telnet.h"
#include "../../header/utils.h"

bool parse_telnet(const uint8_t *buffer, size_t size, telnet_info_t *info)
{
    if (buffer == NULL || size == 0 || info == NULL)
    {
        return false;
    }

    memset(info, 0, sizeof(telnet_info_t));

    /* Check if packet starts with Interpret As Command (IAC) */
    if (buffer[0] == TELNET_IAC)
    {
        info->has_iac = true;

        if (size >= TELNET_MIN_OPTION_CMD_LEN)
        {
            info->command = buffer[1];
            info->option  = buffer[2];
        }
        else if (size >= 2)
        {
            info->command = buffer[1];
        }

        return true;
    }

    /* Standard Telnet plain text traffic */
    info->has_iac = false;
    return true;
}

void print_telnet(const telnet_info_t *info, const uint8_t *payload, size_t payload_size)
{
    if (info == NULL)
    {
        return;
    }

    printf("Layer 5-7\n");
    printf("----------\n");
    printf("Protocol       : Telnet\n");

    if (info->has_iac)
    {
        printf("Type           : Control Command (IAC)\n");
        printf("Command Code   : 0x%02X\n", info->command);
        printf("Option Code    : 0x%02X\n", info->option);
    }
    else
    {
        printf("Type           : Plaintext Data\n");
    }

    print_payload(payload, payload_size);
}