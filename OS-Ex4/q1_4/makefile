CXX=g++
CXXFLAGS=-std=c++11 -Werror -g -fprofile-arcs -ftest-coverage
VALGRIND_FLAGS=-v --leak-check=full --show-leak-kinds=all  --error-exitcode=99
# -pg and gmon file, allocating memory and can cause a memory leak
SOURCES=EulerCircle.cpp
OBJECTS=$(subst .cpp,.o,$(SOURCES))

EulerCircle: $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o EulerCircle $(OBJECTS) -lgcov

valgrind: EulerCircle
	valgrind --tool=memcheck $(VALGRIND_FLAGS) ./EulerCircle 2>&1 | { egrep "lost| at " || true; }

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f *.o EulerCircle *.gcov *.gcda *.gcno gmon.out

.PHONY: clean
# valgrind --leak-check=full -s --show-leak-kinds=all --track-origins=yes ./EulerCircle -v 10 -e 15 -s 42
# valgrind --leak-check=full -s --show-leak-kinds=all --track-origins=yes ./EulerCircle -v 10 -e 15 -s 42 > valgrind_output.txt 2>&1
# valgrind --tool=callgrind ./EulerCircle