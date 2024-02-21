# Makefile for main.c

CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -g

TARGET = conv
SRC = conv.c

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRC)

clean:
	rm -f $(TARGET)
