#ifndef SOCKET_H
#define SOCKET_H

int open_socket();
int get_packet(int sock_r, unsigned char *buffer, int buffer_size);

#endif