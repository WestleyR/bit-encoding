TARGET = bit-test

CC = gcc

SRC = src/main-bit.c

all: $(TARGET)

$(TARGET): $(SRC)
	@$(CC) -Wall -o $(TARGET) $(SRC)

clean: $(TARGET)
	rm -f $(TARGET)

