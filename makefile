# Define compiler
CXX = clang++-9

# Compiler flags
CXXFLAGS = -std=c++14 -Wall -Wextra

.PHONY: all clean

all: kosaraju


# Define compiler
CXX = clang++-9

# Compiler flags
CXXFLAGS = -std=c++14 -Wall -Wextra

# Target executable name
TARGET = Kosaraju

# Source files
SOURCES = Kosaraju.cpp

# Object files
OBJECTS = $(SOURCES:.cpp=.o)

# Rule to make the executable
$(TARGET): $(OBJECTS)
    $(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJECTS)

# Rule to make object files
%.o: %.cpp
    $(CXX) $(CXXFLAGS) -c $< -o $@

# Clean rule
clean:
    rm -f $(TARGET) $(OBJECTS)
