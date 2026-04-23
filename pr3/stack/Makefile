CC = gcc
CFLAGS = -Wall -Wextra -O2 -g
TARGET = stack
IMPL = stack_list

OBJS = $(TARGET).o $(IMPL).o

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

$(TARGET).o: $(TARGET).c stack_item.h
	$(CC) $(CFLAGS) -c $(TARGET).c

$(IMPL).o: $(IMPL).c stack_item.h item.h
	$(CC) $(CFLAGS) -c $(IMPL).c

clean:
	rm -f $(TARGET) $(OBJS)
