CC = gcc
CFLAGS = -Wall -Wextra -O2 -g

.PHONY: all run test clean

TARGET = convex_hull
TEST_TARGET = test_convex_hull

OBJS = convex_hull.o
MAIN_OBJS = main.o $(OBJS)
TEST_OBJS = test_convex_hull.o $(OBJS)

all: $(TARGET)

run: $(TARGET)
	./$(TARGET)

$(TARGET): $(MAIN_OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(MAIN_OBJS) -lm

main.o: main.c convex_hull.h
	$(CC) $(CFLAGS) -c main.c

convex_hull.o: convex_hull.c convex_hull.h
	$(CC) $(CFLAGS) -c convex_hull.c

test_convex_hull.o: test/test_convex_hull.c convex_hull.h
	$(CC) $(CFLAGS) -c test/test_convex_hull.c -o test_convex_hull.o

$(TEST_TARGET): $(TEST_OBJS)
	$(CC) $(CFLAGS) -o $(TEST_TARGET) $(TEST_OBJS) -lm

test: $(TEST_TARGET)
	./$(TEST_TARGET)

clean:
	rm -f $(TARGET) $(TEST_TARGET) *.o
