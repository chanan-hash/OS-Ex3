CXX = g++
CXXFLAGS = -std=c++11 -pg -Wall -g 

SOURCES = Kosaraju.cpp

OBJS = $(SOURCES:.cpp=.o)

TARGET = kosaraju

all: $(TARGET) #run

#run: $(TARGET)
#	for file in *.txt; do \
		echo "Running $$file"; \
		./$(TARGET) < $$file || true; \
	done

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

.cpp.o:
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET) *.o *.gmon *.out