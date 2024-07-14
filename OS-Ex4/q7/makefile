CC = gcc
CFLAGS = -Wall -g -pthread

.PHONY: all clean

all: race

race:
	$(CC) $(CFLAGS) -o race race.c

clean:
	rm -f race *.o