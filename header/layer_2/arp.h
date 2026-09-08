#ifndef ARP_H
#define ARP_H

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

/**
 * @file arp.h
 * @brief ARP (Address Resolution Protocol) parser and printer module.
 */

/* ARP Protocol Constants */
#define ARP_FIXED_HEADER_SIZE 8

/* Header Field Offsets */
#define ARP_HARDWARE_TYPE_OFFSET            0
#define ARP_PROTOCOL_TYPE_OFFSET            2
#define ARP_HARDWARE_ADDRESS_LENGTH_OFFSET  4
#define ARP_PROTOCOL_ADDRESS_LENGTH_OFFSET  5
#define ARP_OPERATION_OFFSET                6

/* Hardware Types and Operations */
#define ARP_HARDWARE_TYPE_ETHERNET          0x0001
#define ARP_OPERATION_REQUEST               0x0001
#define ARP_OPERATION_REPLY                 0x0002

/**
 * @brief Represents a parsed ARP packet header and fields.
 */
typedef struct arp_header
{
    uint16_t hardware_type;               /**< Hardware address space type */
    uint16_t protocol_type;               /**< Protocol address space type */
    uint8_t hardware_address_length;      /**< Length of hardware addresses */
    uint8_t protocol_address_length;      /**< Length of protocol addresses */
    uint16_t operation;                   /**< ARP operation (Request/Reply) */

    const uint8_t *sender_hardware_address; /**< Sender hardware (MAC) address */
    const uint8_t *sender_protocol_address; /**< Sender protocol (IP) address */
    const uint8_t *target_hardware_address; /**< Target hardware (MAC) address */
    const uint8_t *target_protocol_address; /**< Target protocol (IP) address */
} arp_header_t;

/**
 * @brief Parses raw bytes into an ARP header structure.
 *
 * @param buffer Pointer to the raw packet bytes.
 * @param packet_size Total available size of the packet.
 * @param header Pointer to the destination arp_header_t structure.
 * @return true if successfully parsed, false otherwise.
 */
bool parse_arp(
    const uint8_t *buffer,
    size_t packet_size,
    arp_header_t *header
);

/**
 * @brief Prints parsed ARP header details to standard output.
 *
 * @param header Pointer to the parsed arp_header_t structure.
 */
void print_arp(
    const arp_header_t *header
);

#endif /* ARP_H */