CC = gcc
CFLAGS = -Wall -Wextra -O2 -g
TARGET = LLRB_tests
INTERFACE = BST
IMPL = BST

OBJS = $(TARGET).o $(IMPL).o node.o LLRB_ops.o LLRB.o

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

$(TARGET).o: $(TARGET).c $(INTERFACE).h node.h item.h LLRB_ops.h LLRB.h
	$(CC) $(CFLAGS) -c $(TARGET).c

$(IMPL).o: $(IMPL).c $(INTERFACE).h item.h node.h LLRB_ops.h LLRB.h
	$(CC) $(CFLAGS) -c $(IMPL).c

node.o: node.c node.h
	$(CC) $(CFLAGS) -c node.c 

LLRB_ops.o: LLRB_ops.c LLRB_ops.h node.h
	$(CC) $(CFLAGS) -c LLRB_ops.c

LLRB.o: LLRB.c LLRB.h
	$(CC) $(CFLAGS) -c LLRB.c

clean:
	rm -f $(TARGET) $(OBJS) *.o
