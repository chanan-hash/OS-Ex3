CXX = g++
CXXFLAGS = -std=c++11 -Wall -g

all: ProactorMain

.PHONY: clean all

ProactorMain: main.o Proactor.o
	$(CXX) $(CXXFLAGS) -o ProactorMain main.o Proactor.o -lpthread

main.o: main.cpp
	$(CXX) $(CXXFLAGS) -c main.cpp

Proactor.o: Proactor.cpp Proactor.hpp
	$(CXX) $(CXXFLAGS) -c Proactor.cpp

clean:
	rm -f *.o ProactorMain