all: Sudoku.hpp test.cpp gtest-all.cpp
	g++ -c gtest-all.cpp
	g++ -o Sudoku test.cpp gtest-all.o


clean:
	rm -f *.o Sudoku
