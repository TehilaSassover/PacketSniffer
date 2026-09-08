#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#include "../../header/layer_5-7/ftp.h"
#include "../../header/utils.h"

bool parse_ftp(const uint8_t *buffer, size_t size, ftp_info_t *info)
{
    if (buffer == NULL || size == 0 || info == NULL)
    {
        return false;
    }

    memset(info, 0, sizeof(ftp_info_t));

    char line[FTP_LINE_MAX_LEN] = {0};
    size_t line_len = extract_line(buffer, size, line, sizeof(line));

    if (line_len == 0)
    {
        return false;
    }

    /* Check if line starts with a 3-digit response code */
    if (line_len >= FTP_CODE_DIGITS &&
        isdigit((unsigned char)line[0]) &&
        isdigit((unsigned char)line[1]) &&
        isdigit((unsigned char)line[2]))
    {
        info->is_response = true;
        info->response_code = (uint16_t)atoi(line);

        if (line_len > FTP_CODE_ARG_OFFSET)
        {
            strncpy(info->arg, line + FTP_CODE_ARG_OFFSET, FTP_ARG_MAX_LEN - 1);
        }
    }
    else
    {
        info->is_request = true;
        info->is_response = false;
        sscanf(line, "%15s %255s", info->command, info->arg);
    }

    return true;
}

void print_ftp(const ftp_info_t *info, const uint8_t *payload, size_t payload_size)
{
    if (info == NULL)
    {
        return;
    }

    printf("Layer 5-7\n");
    printf("----------\n");
    printf("Protocol      : FTP\n");

    if (info->is_response)
    {
        printf("Type          : Response\n");
        printf("Response Code : %u\n", info->response_code);
        printf("Message       : %s\n", info->arg[0] != '\0' ? info->arg : "None");
    }
    else
    {
        printf("Type          : Command\n");
        printf("Command       : %s\n", info->command);
        printf("Arguments     : %s\n", info->arg[0] != '\0' ? info->arg : "None");
    }

    print_payload(payload, payload_size);
}