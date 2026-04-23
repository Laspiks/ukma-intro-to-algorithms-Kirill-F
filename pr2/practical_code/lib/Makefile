CC = gcc
CFLAGS = -Wall -Wextra -O2 -g
TARGET = statistical_measures

all: lib$(TARGET)_static.a lib$(TARGET)_dynamic.so

lib$(TARGET)_static.a: $(TARGET).o
	ar rcs lib$(TARGET)_static.a $(TARGET).o

lib$(TARGET)_dynamic.so: $(TARGET).o
	$(CC) -shared -o lib$(TARGET)_dynamic.so $(TARGET).o -lm

$(TARGET).o: $(TARGET).c
	$(CC) $(CFLAGS) -fPIC -c $(TARGET).c

clean:
	rm -f lib$(TARGET)_static.a lib$(TARGET)_dynamic.so $(TARGET).o
