#include <iostream>
#include <vector>
#include <algorithm>
#include "SudokuSolver.h"
#include "SudokuGame.h"
#include "SudokuGenerator.h"

#include <iterator>
#include <cstdlib>
#include <ctime>

void SudokuGame::printBoard() {
	for (int i = 0; i < 81; i++) 
		{if (i % 9 == 0 && i != 0) {
			std::cout << "\n";
		}
		std::cout << currentBoard[i] << " ";
	}
}

void SudokuGame::restartGame() {
	currentBoard = startBoard;
}

void SudokuGame::solveGame() {
	SudokuSolver sudokusolver;
	counter = 0;
	sudokusolver.solveBoard(0, startBoard, currentBoard, counter, gameMode);
}

bool SudokuGame::checkWin() {
    if (std::find(currentBoard.begin(), currentBoard.end(), 0) ==
					currentBoard.end()) {
		return true;
	}
	return false;
}
