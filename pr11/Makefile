CC = gcc
CFLAGS = -std=c11 -Wall -Wextra -Wpedantic -O2

TARGET = practical
OBJS = practical.o graph.o

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

practical.o: practical.c graph.h
	$(CC) $(CFLAGS) -c practical.c

graph.o: graph.c graph.h
	$(CC) $(CFLAGS) -c graph.c

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(TARGET) $(OBJS)

.PHONY: all run clean
