#ifndef TELNET_H
#define TELNET_H

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

/* Telnet Command Constants */
#define TELNET_IAC                  0xFF
#define TELNET_DONT                 0xFE  
#define TELNET_DO                   0xFD  
#define TELNET_WONT                 0xFC 
#define TELNET_WILL                 0xFB 
#define TELNET_SB                   0xFA  
#define TELNET_SE                   0xF0    

#define TELNET_MIN_OPTION_CMD_LEN   3

typedef struct {
    bool has_iac;
    uint8_t command;
    uint8_t option;
} telnet_info_t;

/**
 * @brief Parses Telnet commands (IAC) or plaintext.
 * @param buffer Raw packet buffer.
 * @param size Buffer size in bytes.
 * @param info Output structure for Telnet data.
 * @return true on success, false otherwise.
 */
bool parse_telnet(const uint8_t *buffer, size_t size, telnet_info_t *info);

/**
 * @brief Prints Telnet command/data status and payload.
 * @param info Parsed Telnet structure.
 * @param payload Payload buffer.
 * @param payload_size Payload size in bytes.
 */
void print_telnet(const telnet_info_t *info, const uint8_t *payload, size_t payload_size);

#endif /* TELNET_H */