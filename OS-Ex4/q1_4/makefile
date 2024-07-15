CXX=g++
CXXFLAGS=-std=c++11 -Werror -g -fprofile-arcs -ftest-coverage
VALGRIND_FLAGS=-v --leak-check=full --show-leak-kinds=all  --error-exitcode=99
# -pg and gmon file, allocating memory and can cause a memory leak
SOURCES=Euler_circle.cpp
OBJECTS=$(subst .cpp,.o,$(SOURCES))

Euler_circle: $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o Euler_circle $(OBJECTS) -lgcov

valgrind: Euler_circle
	valgrind --tool=memcheck $(VALGRIND_FLAGS) ./Euler_circle 2>&1 | { egrep "lost| at " || true; }

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f *.o Euler_circle *.gcov *.gcda *.gcno gmon.out

.PHONY: clean
# valgrind --leak-check=full -s --show-leak-kinds=all --track-origins=yes ./Euler_circle -v 10 -e 15 -s 42
# valgrind --leak-check=full -s --show-leak-kinds=all --track-origins=yes ./Euler_circle -v 10 -e 15 -s 42 > valgrind_output.txt 2>&1
# valgrind --tool=callgrind ./Euler_circle