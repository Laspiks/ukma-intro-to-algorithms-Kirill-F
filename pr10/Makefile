CC = gcc
CFLAGS = -std=c11 -Wall -Wextra -Wpedantic -O2
LDFLAGS = -lm

TARGET = parking_problem
SRC = parking_problem.c

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) $(SRC) -o $(TARGET) $(LDFLAGS)

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(TARGET)

.PHONY: all run clean
