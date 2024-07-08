CXX = g++
CXXFLAGS = -std=c++11 -Wall -g 

SOURCES = Kosaraju.cpp

OBJS = $(SOURCES:.cpp=.o)

TARGET = kosaraju

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

.cpp.o:
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)