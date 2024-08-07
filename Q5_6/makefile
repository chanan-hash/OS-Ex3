CXX = g++
CXXFLAGS = -std=c++11 -Wall -g

.PHONY: clean all

# Target executable
TARGET = reactor_program

# Source files
SRCS = main.cpp Reactor.cpp #Reactor.hpp

# Object files
OBJS = $(SRCS:.cpp=.o)

# Default target
all: $(TARGET)

# Rule to link the executable
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Rule to compile source files into object files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean up build files
clean:
	rm -f *.o $(TARGET)