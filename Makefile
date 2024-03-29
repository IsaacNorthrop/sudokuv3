# Makefile for main.c

CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -g

TARGET = sudoku
SRC = sudoku.c

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRC)

clean:
	rm -f $(TARGET)
