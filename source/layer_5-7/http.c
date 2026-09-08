#include <stdio.h>
#include <string.h>

#include "../../header/layer_5-7/http.h"
#include "../../header/utils.h"

bool parse_http(const uint8_t *buffer, size_t size, http_info_t *info)
{
    if (buffer == NULL || size == 0 || info == NULL)
    {
        return false;
    }

    memset(info, 0, sizeof(http_info_t));

    char first_line[HTTP_FIRST_LINE_MAX_LEN] = {0};
    size_t line_len = extract_line(buffer, size, first_line, sizeof(first_line));

    if (line_len == 0)
    {
        return false;
    }

    if (strncmp(first_line, HTTP_RESPONSE_PREFIX, HTTP_PREFIX_LEN) == 0)
    {
        info->is_request = false;
        sscanf(first_line, "%15s %255s", info->version, info->uri);
        strncpy(info->method, "RESPONSE", HTTP_METHOD_MAX_LEN - 1);
    }
    else
    {
        info->is_request = true;
        int parsed = sscanf(first_line, "%15s %255s %15s", info->method, info->uri, info->version);
        if (parsed < HTTP_SCAN_MIN_FIELDS)
        {
            return false;
        }
    }

    return true;
}

void print_http(const http_info_t *info, const uint8_t *payload, size_t payload_size)
{
    if (info == NULL)
    {
        return;
    }

    /* שימוש בפונקציית העזר מ-utils להדפסת הכותרת */
    print_layer_header("Layer 5-7", "HTTP");

    if (info->is_request)
    {
        printf("Method   : %s\n", info->method);
        printf("URI      : %s\n", info->uri);
        printf("Version  : %s\n", info->version[0] != '\0' ? info->version : "N/A");
    }
    else
    {
        printf("Type     : Response\n");
        printf("Version  : %s\n", info->version);
        printf("Status   : %s\n", info->uri);
    }

    print_payload(payload, payload_size);
}