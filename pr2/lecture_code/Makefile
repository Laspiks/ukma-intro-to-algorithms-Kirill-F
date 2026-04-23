# Makefile for the fixed program

CC = gcc
CFLAGS = -Wall -Wextra -O2 -g
TARGET = main

all: $(TARGET)

$(TARGET): $(TARGET).o
	$(CC) $(CFLAGS) -o $(TARGET) $(TARGET).o

$(TARGET).o: $(TARGET).c
	$(CC) $(CFLAGS) -c $(TARGET).c

clean:
	rm -f $(TARGET) $(TARGET).o
