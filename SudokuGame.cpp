#include <iostream>
#include <vector>
#include <algorithm>
#include "SudokuSolver.h"
#include "SudokuGame.h"

void SudokuGame::printBoard() {
	for (int i = 0; i < 81; i++) {
		if (i % 9 == 0 && i != 0) {
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
	sudokusolver.solveBoard(0, startBoard, currentBoard);
}

bool SudokuGame::checkWin() {
    if (std::find(currentBoard.begin(), currentBoard.end(), 0) ==
					currentBoard.end()) {
		return true;
	}
	return false;
}

