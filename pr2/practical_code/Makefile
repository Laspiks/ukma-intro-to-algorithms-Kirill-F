CC = gcc
CFLAGS = -Wall -Wextra -O2 -g
TARGET = main
LIB_DIR = ./lib
LIB_DYNAMIC = $(LIB_DIR)/libstatistical_measures_dynamic.so
LIB_STATIC = $(LIB_DIR)/libstatistical_measures_static.a

all: $(TARGET)_dynamic $(TARGET)_static

$(TARGET)_dynamic: $(TARGET).o $(LIB_DYNAMIC)
	$(CC) $(CFLAGS) -o $(TARGET)_dynamic $(TARGET).o -L$(LIB_DIR) -lstatistical_measures_dynamic -lm -Wl,-rpath=$(LIB_DIR)

$(TARGET)_static: $(TARGET).o $(LIB_STATIC)
	$(CC) $(CFLAGS) -o $(TARGET)_static $(TARGET).o $(LIB_STATIC) -lm

$(TARGET).o: $(TARGET).c
	$(CC) $(CFLAGS) -c $(TARGET).c

$(LIB_DYNAMIC) $(LIB_STATIC):
	$(MAKE) -C $(LIB_DIR)

clean:
	rm -f $(TARGET)_dynamic $(TARGET)_static $(TARGET).o
