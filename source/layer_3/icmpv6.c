#include <stdio.h>
#include <string.h>
#include <arpa/inet.h>
#include "layer_3/icmpv6.h"

bool parse_icmpv6(const uint8_t *buffer, size_t packet_size, icmpv6_header_t *header) {
    if (buffer == NULL || header == NULL || packet_size < ICMPV6_HEADER_MIN_SIZE) {
        return false;
    }

    header->type = buffer[0];
    header->code = buffer[1];

    uint16_t raw_checksum;
    memcpy(&raw_checksum, buffer + 2, sizeof(raw_checksum));
    header->checksum = ntohs(raw_checksum);

    uint16_t raw_rest1;
    uint16_t raw_rest2;
    memcpy(&raw_rest1, buffer + 4, sizeof(raw_rest1));
    memcpy(&raw_rest2, buffer + 6, sizeof(raw_rest2));

    header->rest_of_header_1 = ntohs(raw_rest1);
    header->rest_of_header_2 = ntohs(raw_rest2);

    return true;
}

void print_icmpv6(const icmpv6_header_t *header) {
    if (header == NULL) {
        return;
    }

    printf("Layer 3 / 4\n");
    printf("--------\n");
    printf("Protocol        : ICMPv6\n");
    printf("Type            : %u ", header->type);

    switch (header->type) {
        case ICMPV6_TYPE_DEST_UNREACHABLE:
            printf("(Destination Unreachable)\n");
            break;
        case ICMPV6_TYPE_PACKET_TOO_BIG:
            printf("(Packet Too Big)\n");
            break;
        case ICMPV6_TYPE_TIME_EXCEEDED:
            printf("(Time Exceeded)\n");
            break;
        case ICMPV6_TYPE_PARAM_PROBLEM:
            printf("(Parameter Problem)\n");
            break;
        case ICMPV6_TYPE_ECHO_REQUEST:
            printf("(Echo Request)\n");
            break;
        case ICMPV6_TYPE_ECHO_REPLY:
            printf("(Echo Reply)\n");
            break;
        case ICMPV6_TYPE_ROUTER_SOLICIT:
            printf("(Router Solicitation)\n");
            break;
        case ICMPV6_TYPE_ROUTER_ADVERT:
            printf("(Router Advertisement)\n");
            break;
        case ICMPV6_TYPE_NEIGHBOR_SOLICIT:
            printf("(Neighbor Solicitation)\n");
            break;
        case ICMPV6_TYPE_NEIGHBOR_ADVERT:
            printf("(Neighbor Advertisement)\n");
            break;
        default:
            printf("(Other/Unassigned)\n");
            break;
    }

    printf("Code            : %u\n", header->code);
    printf("Checksum        : 0x%04X\n", header->checksum);

    if (header->type == ICMPV6_TYPE_ECHO_REQUEST || header->type == ICMPV6_TYPE_ECHO_REPLY) {
        printf("Identifier      : %u (0x%04X)\n", header->rest_of_header_1, header->rest_of_header_1);
        printf("Sequence Number : %u (0x%04X)\n", header->rest_of_header_2, header->rest_of_header_2);
    } else {
        printf("Rest of Header  : 0x%04X%04X\n", header->rest_of_header_1, header->rest_of_header_2);
    }
}