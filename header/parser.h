#ifndef PARSER_H
#define PARSER_H

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

bool parse_packet(
    const uint8_t *buffer,
    size_t packet_size
);

#endif