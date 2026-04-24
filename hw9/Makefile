CC = gcc
CFLAGS = -Wall -Wextra -O2 -g

# Main target
TARGET = maze_client
TEST_TARGET = test_graph

# Object files
OBJS = maze_client.o maze.o graph.o queue.o
TEST_OBJS = test_graph.o graph.o queue.o

# Default target
all: $(TARGET) $(TEST_TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

$(TEST_TARGET): $(TEST_OBJS)
	$(CC) $(CFLAGS) -o $(TEST_TARGET) $(TEST_OBJS)

maze_client.o: maze_client.c maze.h graph.h
	$(CC) $(CFLAGS) -c maze_client.c

maze.o: maze.c maze.h
	$(CC) $(CFLAGS) -c maze.c

graph.o: graph.c graph.h queue.h
	$(CC) $(CFLAGS) -c graph.c

queue.o: queue.c queue.h
	$(CC) $(CFLAGS) -c queue.c

test_graph.o: test/test_graph.c graph.h
	$(CC) $(CFLAGS) -c test/test_graph.c -o test_graph.o

# Clean everything
clean:
	rm -f $(TARGET) $(TEST_TARGET) *.o
