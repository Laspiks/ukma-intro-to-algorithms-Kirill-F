CC = gcc
CFLAGS = -Wall -Wextra -O2 -g
TARGET = lecture_7
IMPL = unordered_array

OBJS = $(TARGET).o $(IMPL).o

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

$(TARGET).o: $(TARGET).c priority_queue.h
	$(CC) $(CFLAGS) -c $(TARGET).c

$(IMPL).o: $(IMPL).c priority_queue.h item.h
	$(CC) $(CFLAGS) -c $(IMPL).c

clean:
	rm -f $(TARGET) $(OBJS)
