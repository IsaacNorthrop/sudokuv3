# Makefile for main.c

CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -g

TARGET = sudoku
SRC = main.c

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRC)

clean:
	rm -f $(TARGET)
