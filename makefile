CC = gcc

CFLAGS = -Wall -Wextra -Iheader

TARGET = packet_sniffer

SRC = main.c \
      source/packet.c \
      source/socket.c

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) $(SRC) -o $(TARGET)

clean:
	rm -f $(TARGET)

re: clean all

.PHONY: all clean re