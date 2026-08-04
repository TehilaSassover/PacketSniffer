#include "../header/parser.h"
#include "../header/layer_2/ethernet.h"

void parse_packet(const unsigned char *buffer,int packet_size)
{
    parse_ethernet(buffer, packet_size);
}