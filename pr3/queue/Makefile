CC = gcc
CFLAGS = -Wall -Wextra -O2 -g
TARGET = queue
IMPL = queue_list

OBJS = $(TARGET).o $(IMPL).o

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

$(TARGET).o: $(TARGET).c queue.h
	$(CC) $(CFLAGS) -c $(TARGET).c

$(IMPL).o: $(IMPL).c queue.h item.h
	$(CC) $(CFLAGS) -c $(IMPL).c

clean:
	rm -f $(TARGET) $(OBJS)
