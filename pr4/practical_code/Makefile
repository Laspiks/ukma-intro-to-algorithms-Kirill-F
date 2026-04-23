CC = gcc
CFLAGS = -Wall -Wextra -O2

all: qsort_example shell_sort_example

qsort_example: qsort_example.c
	$(CC) $(CFLAGS) -o $@ $<

shell_sort_example: shell_sort_example.c
	$(CC) $(CFLAGS) -o $@ $<

clean:
	rm -f qsort_example shell_sort_example
