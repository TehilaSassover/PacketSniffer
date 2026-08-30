#ifndef UTILS_H
#define UTILS_H

#include <stddef.h>
#include <stdint.h>

#define MAC_ADDRESS_SIZE 6
#define IPV4_ADDRESS_SIZE 4

uint16_t read_uint16_be(const uint8_t *buffer);
uint32_t read_uint32_be(const uint8_t *buffer);
void print_mac(const uint8_t *mac);
void print_ipv4(const uint8_t *ip);
void print_bytes_hex(const uint8_t *buffer, size_t length);

#endif