CXX = g++
CXXFLAGS = -std=c++11 -pg -Wall -g 

.PHONY: all clean

all: kosaraju

kosaraju: kosaraju.cpp
	$(CXX) $(CXXFLAGS) -o kosaraju kosaraju.cpp

clean:
	rm -f kosaraju *.o *.gmon *.out
