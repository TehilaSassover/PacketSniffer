#include <stdio.h>
#include <string.h>

#include "../../header/layer_5-7/ssh.h"
#include "../../header/utils.h"

bool parse_ssh(const uint8_t *buffer, size_t size, ssh_info_t *info)
{
    if (buffer == NULL || size == 0 || info == NULL)
    {
        return false;
    }

    memset(info, 0, sizeof(ssh_info_t));

    char line[SSH_LINE_MAX_LEN] = {0};
    size_t line_len = extract_line(buffer, size, line, sizeof(line));

    if (line_len == 0)
    {
        return false;
    }

    if (strncmp(line, SSH_IDENTIFIER_PREFIX, SSH_PREFIX_LEN) == 0)
    {
        info->is_valid_banner = true;
        strncpy(info->version_string, line, SSH_VERSION_MAX_LEN - 1);
        return true;
    }

    return false;
}

void print_ssh(const ssh_info_t *info, const uint8_t *payload, size_t payload_size)
{
    if (info == NULL)
    {
        return;
    }

    printf("Layer 5-7\n");
    printf("----------\n");
    printf("Protocol       : SSH\n");

    if (info->is_valid_banner)
    {
        printf("Banner         : %s\n", info->version_string);
    }
    else
    {
        printf("Status         : Encrypted Payload / Unknown Banner\n");
    }

    print_payload(payload, payload_size);
}