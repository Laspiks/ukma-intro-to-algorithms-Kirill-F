CC = gcc
CFLAGS = -Wall -Wextra -O2 -g

.PHONY: all run test clean

# Main target
TARGET = lecture_12

TEST_TARGET = test_paths

OBJS = digraph.o paths.o dfs.o bfs.o queue.o

# Object files for main program
MAIN_OBJS = $(TARGET).o $(OBJS)

# Object files for DFS test
TEST_OBJS = test_paths.o $(OBJS)

# Default target
all: run

run: $(TARGET)
	./$(TARGET)

$(TARGET): $(MAIN_OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(MAIN_OBJS)

$(TARGET).o: $(TARGET).c digraph.h paths_helper.h
	$(CC) $(CFLAGS) -c $(TARGET).c

digraph.o: digraph.c digraph.h paths_helper.h
	$(CC) $(CFLAGS) -c digraph.c 

dfs.o: dfs.h dfs.c
	$(CC) $(CFLAGS) -c dfs.c

bfs.o: bfs.c bfs.h queue.h
	$(CC) $(CFLAGS) -c bfs.c

queue.o: queue.c queue.h
	$(CC) $(CFLAGS) -c queue.c

paths.o: paths.c paths.h paths_helper.h digraph.h
	$(CC) $(CFLAGS) -c paths.c

$(TEST_TARGET).o: test/test_paths.c dfs.h paths.h paths_helper.h digraph.h bfs.h queue.h
	$(CC) $(CFLAGS) -c test/test_paths.c -o test_paths.o

# Test target
$(TEST_TARGET): $(TEST_OBJS)
	$(CC) $(CFLAGS) -o test_paths $(TEST_OBJS)

test: $(TEST_TARGET)

# Clean everything
clean:
	rm -f $(TARGET) test_paths *.o
