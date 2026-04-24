CC = gcc
CFLAGS = -Wall -Wextra -O2 -g
TARGET = hash_demo

# List of object files
OBJS = hash_demo.o hash_code.o

# Default target
all: $(TARGET)

# Link the object files to create the final executable
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

# Compile hash_demo.c to hash_demo.o
hash_demo.o: hash_demo.c hash_code.h item.h
	$(CC) $(CFLAGS) -c hash_demo.c

# Compile hash_code.c to hash_code.o
hash_code.o: hash_code.c hash_code.h
	$(CC) $(CFLAGS) -c hash_code.c

# Clean up build files
clean:
	rm -f $(TARGET) $(OBJS)
