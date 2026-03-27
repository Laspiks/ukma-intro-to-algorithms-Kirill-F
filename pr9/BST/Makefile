CC = gcc
CFLAGS = -Wall -Wextra -O2 -g
TARGET = lecture_8
INTERFACE = BST
IMPL = BST

OBJS = $(TARGET).o $(IMPL).o node.o  # Add node.o

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

$(TARGET).o: $(TARGET).c $(INTERFACE).h node.h item.h
	$(CC) $(CFLAGS) -c $(TARGET).c

$(IMPL).o: $(IMPL).c $(INTERFACE).h item.h node.h
	$(CC) $(CFLAGS) -c $(IMPL).c

node.o: node.c node.h
	$(CC) $(CFLAGS) -c node.c 

clean:
	rm -f $(TARGET) $(OBJS) *.o
