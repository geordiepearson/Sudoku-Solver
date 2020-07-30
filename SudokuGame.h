#ifndef SUDOKUGAME_H_
#define SUDOKUGAME_H_

#define BOARD_SIZE 81
#define ROW_SIZE 9

#include <vector>
#include <string>

class SudokuGame {
public:
	// A model of the original Sudoku puzzle
    std::vector<int> startBoard = std::vector<int>(81);
    // A model of the Sudoku puzzle at the current moment.
    std::vector<int> currentBoard = std::vector<int>(81);
    // A model of the Sudoku puzzle when solved.
    std::vector<int> solvedBoard = std::vector<int>(81);
	// The current state of the game with 
	bool gameMode = true;
    int counter;
	std::string title = "Let's Play Sudoku";
    int time = 0;

	void printBoard();
	
	void restartGame();

	void solveGame();

	void saveGame();

	void loadGame();

	bool checkWin();

};
#endif /*SUDOKUGAME_H_*/
