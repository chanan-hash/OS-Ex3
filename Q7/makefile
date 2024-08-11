CXX = g++
CXXFLAGS = -std=c++11 -Wall -g

all: ThreadUsers

.PHONY: clean all

ThreadUsers: ThreadUsers.o
	$(CXX) $(CXXFLAGS) -o ThreadUsers ThreadUsers.o -lpthread

ThreadUsers.o: ThreadUsers.cpp
	$(CXX) $(CXXFLAGS) -c ThreadUsers.cpp

clean:
	rm -f *.o ThreadUsers