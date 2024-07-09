CXX = g++
CXXFLAGS = -std=c++11 -g -Wall

.PHONY: all clean

all: MultiUsers

MultiUsers: MultiUsers.cpp
	$(CXX) $(CXXFLAGS) -o MultiUsers MultiUsers.cpp

clean:
	rm -f *.o MultiUsers