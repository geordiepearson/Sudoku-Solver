#ifndef SUDOKUGAME_H_
#define SUDOKUGAME_H_

#define BOARD_SIZE 81
#define ROW_SIZE 9

#include <vector>
#include <string>

class SudokuGame {
public:
	// A model of the original Sudoku puzzle
	std::vector<int> startBoard {
		0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0
		};
	// A model of the Sudoku Puzzle at the current moment
	std::vector<int> currentBoard {
		2, 9, 5, 7, 4, 3, 8, 6, 1,
		4, 3, 1, 8, 6, 5, 9, 0, 0,
		8, 7, 6, 1, 9, 2, 5, 4, 3,
		3, 8, 7, 4, 5, 9, 2, 1, 6,
		6, 1, 2, 3, 8, 7, 4, 9, 5,
		5, 4, 9, 2, 1, 6, 7, 3, 8,
		7, 6, 3, 5, 3, 4, 1, 8, 9,
		9, 2, 8, 6, 7, 1, 3, 5, 4,
		1, 5, 4, 9, 3, 8, 6, 0, 0
		};
	
	std::vector<int> solvedBoard {
		0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0
		};

	bool gameMode = true;
	int counter;
	std::string title = "Let's Play Sudoku";
	void printBoard();
	
	void restartGame();

	void solveGame();

	bool checkWin();

};
#endif /*SUDOKUGAME_H_*/
