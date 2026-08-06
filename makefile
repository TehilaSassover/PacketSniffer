CC = gcc

CFLAGS = -Wall -Wextra -Iheader

TARGET = packet_sniffer
TEST_TARGET = test_packet

SRC = main.c \
      $(wildcard source/*.c) \
      $(wildcard source/layer_2/*.c)

TEST_SRC = test_packet.c \
           source/parser.c \
           source/utils.c \
           $(wildcard source/layer_2/*.c)


all: $(TARGET)


$(TARGET): $(SRC)
	$(CC) $(CFLAGS) $(SRC) -o $(TARGET)


$(TEST_TARGET): $(TEST_SRC)
	$(CC) $(CFLAGS) $(TEST_SRC) -o $(TEST_TARGET)


test: $(TEST_TARGET)


clean:
	rm -f $(TARGET) $(TEST_TARGET)


re: clean all


.PHONY: all test clean re