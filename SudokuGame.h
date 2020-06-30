#ifndef SUDOKUGAME_H_
#define SUDOKUGAME_H_

#define BOARD_SIZE 81
#define ROW_SIZE 9

#include <vector>

class SudokuGame {
public:
	// A vector containing the indexes of squares in the Sudoku puzzle 
	// which values are given at the start of the puzzle
	std::vector<int> givenIndexes {6, 10, 14, 16, 18, 20, 24, 28, 31, 39, 
		41, 49, 52, 56, 60, 62, 64, 66, 70, 73};
	// A model of the original Sudoku puzzle
	std::vector<int> startBoard {
		0, 0, 0, 0, 0, 0, 2, 0, 0,
		0, 8, 0, 0, 0, 7, 0, 9, 0,
		6, 0, 2, 0, 0, 0, 5, 0, 0,
		0, 7, 0, 0, 6, 0, 0, 0, 0,
		0, 0, 0, 9, 0, 1, 0, 0, 0, 
		0, 0, 0, 0, 2, 0, 0, 4, 0,
		0, 0, 5, 0, 0, 0, 6, 0, 3,
		0, 9, 0, 4, 0, 0, 0, 7, 0,
		0, 0, 6, 0, 0, 0, 0, 0, 0
		};
	// A model of the Sudoku Puzzle at the current moment
	std::vector<int> currentBoard {
		0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 8, 0, 0, 0, 7, 0, 9, 0,
		6, 0, 2, 0, 0, 0, 5, 0, 0,
		0, 7, 0, 0, 6, 0, 0, 0, 0,
		0, 0, 0, 9, 0, 1, 0, 0, 0, 
		0, 0, 0, 0, 2, 0, 0, 4, 0,
		0, 0, 5, 0, 0, 0, 6, 0, 3,
		0, 9, 0, 4, 0, 0, 0, 7, 0,
		0, 0, 6, 0, 0, 0, 0, 0, 0
		};
	
	void restartGame();

	void solveGame();

	void toggleScript();
};

#endif /*SUDOKUGAME_H_*/
