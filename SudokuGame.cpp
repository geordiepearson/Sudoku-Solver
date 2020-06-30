#include <iostream>
#include <vector>
#include "SudokuSolver.h"
#include "SudokuGame.h"

void SudokuGame::restartGame() {
	currentBoard = startBoard;
}

void SudokuGame::solveGame() {
	SudokuSolver sudokusolver;
	sudokusolver.solveBoard(0, currentBoard, givenIndexes);
}

void SudokuGame::toggleScript() {
	return;
}

