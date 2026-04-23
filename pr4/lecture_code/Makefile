CC = gcc
CFLAGS = -Wall -Wextra -O2 -g
TARGET = lecture_4

OBJS = $(TARGET).o 

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

$(TARGET).o: $(TARGET).c 
	$(CC) $(CFLAGS) -c $(TARGET).c

clean:
	rm -f $(TARGET) $(OBJS)
