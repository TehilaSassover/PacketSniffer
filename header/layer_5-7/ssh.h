#ifndef SSH_H
#define SSH_H

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

/* SSH Constants */
#define SSH_LINE_MAX_LEN        512
#define SSH_VERSION_MAX_LEN     64
#define SSH_IDENTIFIER_PREFIX   "SSH-"
#define SSH_PREFIX_LEN          4

typedef struct {
    char version_string[SSH_VERSION_MAX_LEN];
    bool is_valid_banner;
} ssh_info_t;

/**
 * @brief Parses SSH version banner.
 * @param buffer Raw packet buffer.
 * @param size Buffer size in bytes.
 * @param info Output structure for SSH banner info.
 * @return true if valid banner found, false otherwise.
 */
bool parse_ssh(const uint8_t *buffer, size_t size, ssh_info_t *info);

/**
 * @brief Prints parsed SSH banner or session status and payload.
 * @param info Parsed SSH structure.
 * @param payload Payload buffer.
 * @param payload_size Payload size in bytes.
 */
void print_ssh(const ssh_info_t *info, const uint8_t *payload, size_t payload_size);

#endif /* SSH_H */