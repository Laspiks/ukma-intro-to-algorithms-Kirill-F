CC = gcc
PATH_TO_HASH = ../hash
CFLAGS = -Wall -Wextra -O2 -g -I$(PATH_TO_HASH)

TARGET = main
TEST_TARGET = test/test_hash

INTERFACE = hash_table
IMPL = separate_chaining_impl # or open_addressing_impl

VPATH = $(PATH_TO_HASH)

COMMON_OBJS = $(IMPL).o hash_code.o
MAIN_OBJS = $(TARGET).o $(COMMON_OBJS)
TEST_OBJS = test_hash.o $(COMMON_OBJS)

all: $(TARGET) $(TEST_TARGET)

# Main binary
$(TARGET): $(MAIN_OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(MAIN_OBJS)

$(TARGET).o: $(TARGET).c $(INTERFACE).h
	$(CC) $(CFLAGS) -c $(TARGET).c

# Test binary
$(TEST_TARGET): $(TEST_OBJS)
	$(CC) $(CFLAGS) -o $(TEST_TARGET) $(TEST_OBJS)

test_hash.o: test/test_hash.c $(INTERFACE).h
	$(CC) $(CFLAGS) -c test/test_hash.c -o test_hash.o

# Common object files
$(IMPL).o: $(IMPL).c $(INTERFACE).h item.h
	$(CC) $(CFLAGS) -c $(IMPL).c

hash_code.o: hash_code.c hash_code.h
	$(CC) $(CFLAGS) -c $(PATH_TO_HASH)/hash_code.c -o hash_code.o

clean:
	rm -f $(TARGET) $(TEST_TARGET) *.o test_hash.o
