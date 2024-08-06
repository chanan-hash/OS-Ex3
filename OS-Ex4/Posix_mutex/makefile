CC = g++
CXXFLAGS = -std=c++17 -pthread -Wall -g

.PHONY: all clean

all: singleton guard

singleton: singleton.o
	$(CC) $(CXXFLAGS) -o $@ $^

guard: guard.o
	$(CC) $(CXXFLAGS) -o $@ $^

singleton.o: singleton.cpp
	$(CC) $(CXXFLAGS) -c $<

guard.o: guard.cpp
	$(CC) $(CXXFLAGS) -c $<

clean:
	rm -f *.o singleton guard