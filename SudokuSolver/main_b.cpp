#include "Sudoku.hpp"
#include <fstream>
#include <iostream>

using namespace std;

int main(){
  ifstream puzzleIn;
  ifstream answerIn;
  puzzleIn.open("evil.txt");
  answerIn.open("evil.answer");
  Sudoku puzzle;
  Sudoku answer;

  puzzleIn >> puzzle;
  answerIn >> answer;
  
  if(puzzle.solve()){
	  cout << "solved!!" << endl;
  }
  else{
	  cout << "Failed!!" << endl;
  }
	cout << "puzzle:" << endl;
  for (int i = 0; i < 9; ++i)
  {
    for (int j = 0; j < 9; ++j)
    {
      cout << puzzle.getValue(i, j) << "  ";
    }
	cout << "\n";
  }
	cout << "answer:" << endl;
  for (int i = 0; i < 9; ++i)
  {
    for (int j = 0; j < 9; ++j)
    {
      cout << answer.getValue(i, j) << "  ";
    }
	cout << "\n";
  }
	return 0;
}