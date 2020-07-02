#ifndef SUDOKUGAME_H_
#define SUDOKUGAME_H_

#define BOARD_SIZE 81
#define ROW_SIZE 9

#include <vector>

class SudokuGame {
public:
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
	
	void printBoard();
	
	void restartGame();

	void solveGame();

	bool checkWin();

};
#endif /*SUDOKUGAME_H_*/
