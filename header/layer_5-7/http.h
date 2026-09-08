#ifndef HTTP_H
#define HTTP_H

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

#define HTTP_METHOD_MAX_LEN  16
#define HTTP_URI_MAX_LEN     256
#define HTTP_VERSION_MAX_LEN 16

#define HTTP_FIRST_LINE_MAX_LEN 512
#define HTTP_RESPONSE_PREFIX     "HTTP/"
#define HTTP_PREFIX_LEN          5
#define HTTP_SCAN_MIN_FIELDS     2

typedef struct {
    char method[HTTP_METHOD_MAX_LEN];
    char uri[HTTP_URI_MAX_LEN];
    char version[HTTP_VERSION_MAX_LEN];
    bool is_request;
} http_info_t;

/**
 * @brief Parses HTTP request or response line.
 * @param buffer Raw packet buffer.
 * @param size Buffer size in bytes.
 * @param info Output structure for parsed HTTP data.
 * @return true on success, false otherwise.
 */
bool parse_http(const uint8_t *buffer, size_t size, http_info_t *info);

/**
 * @brief Prints parsed HTTP fields and payload in both HEX and ASCII.
 * @param info Parsed HTTP structure.
 * @param payload Payload buffer.
 * @param payload_size Payload size in bytes.
 */
void print_http(const http_info_t *info, const uint8_t *payload, size_t payload_size);

#endif /* HTTP_H */