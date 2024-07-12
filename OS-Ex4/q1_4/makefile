CXX=g++
CXXFLAGS=-std=c++11 -Werror -Wsign-conversion -pg -g -fprofile-arcs -ftest-coverage
VALGRIND_FLAGS=-v --leak-check=full --show-leak-kinds=all  --error-exitcode=99

SOURCES=Euler_circle.cpp
OBJECTS=$(subst .cpp,.o,$(SOURCES))

Euler_circle: $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o EulerCircle $(OBJECTS) -lgcov

valgrind: Euler_circle
	valgrind --tool=memcheck $(VALGRIND_FLAGS) ./EulerCircle 2>&1 | { egrep "lost| at " || true; }

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f *.o Euler_circle *.gcov *.gcda *.gcno gmon.out

.PHONY: clean