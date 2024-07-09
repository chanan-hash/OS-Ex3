CXX = g++
CXXFLAGS = -std=c++11 -pg -Wall -g 

all: kosaraju_list kosaraju_matrix

kosaraju_list: kosaraju_list.cpp
	$(CXX) $(CXXFLAGS) -o kosaraju_list kosaraju_list.cpp

kosaraju_matrix:
	$(CXX) $(CXXFLAGS) -o kosaraju_matrix kosaraju_matrix.cpp

clean:
	rm -f kosaraju_list kosaraju_matrix $(TARGET) *.o *.gmon *.out
