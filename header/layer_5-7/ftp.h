#ifndef FTP_H
#define FTP_H

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

/* FTP Constants */
#define FTP_COMMAND_MAX_LEN 16
#define FTP_ARG_MAX_LEN     256
#define FTP_LINE_MAX_LEN    512

#define FTP_CODE_DIGITS     3
#define FTP_CODE_ARG_OFFSET 4

typedef struct {
    bool is_request;
    char command[FTP_COMMAND_MAX_LEN];
    char arg[FTP_ARG_MAX_LEN];
    bool is_response;
    uint16_t response_code;
} ftp_info_t;

/**
 * @brief Parses FTP commands or response codes.
 * @param buffer Raw packet buffer.
 * @param size Buffer size in bytes.
 * @param info Output structure for parsed FTP data.
 * @return true on successful parse, false otherwise.
 */
bool parse_ftp(const uint8_t *buffer, size_t size, ftp_info_t *info);

/**
 * @brief Prints parsed FTP information and payload.
 * @param info Parsed FTP structure.
 * @param payload Payload buffer.
 * @param payload_size Payload size in bytes.
 */
void print_ftp(const ftp_info_t *info, const uint8_t *payload, size_t payload_size);

#endif /* FTP_H */