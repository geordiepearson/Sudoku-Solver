#include "SudokuGenerator.h"
#include "SudokuGame.h"

#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <cstdlib>
#include <fstream>
#include <string>
#include <ctime>

int SudokuGenerator::convertToBox(int row, int column) {
	int box;
	if (column < 4) {
		if (row < 4) {
			box = 1;
		} else if (row < 7) {
			box = 4;
		} else if (row < 10) {
			box = 7;
		}
	} else if (column < 7) {
		if (row < 4) {
			box = 2;
		} else if (row < 7) {
			box = 5;
		} else if (row < 10) {
			box = 8;
		}
	} else if (column < 10) {
		if (row < 4) {
			box = 3;
		} else if (row < 7) {
			box = 6;
		} else if (row < 10) {
			box = 9;
		}
	}
    return box;
}

void SudokuGenerator::placeValue(std::vector<int> &board, int squareValue) {
	// The rows in the Sudoku board that the given squareValue can be placed 
	// into.
	std::vector<int> avaliableRows {1, 2, 3, 4, 5, 6, 7, 8, 9};
	// The boxes in the Sudoku board that the given squareValue can be placed 
	// into.
	std::vector<int> avaliableBoxes {1, 2, 3, 4, 5, 6, 7, 8, 9};
	// Indicates whether a valid row to place the squareValue has been found.
	bool foundRow;
	// The randomly selected row which is being tested for validity.
	int row;
	// The index of the square on the Sudoku board model corresponding to the 
	// start of the given row.
	int rowIndex;
	// Indicates whether a valid box to place the squareValue has been found.
	bool foundBox;
	// The box corresponding to the randomly selected row .
	int box;
	// The index of the square on the Sudoku board model corresponding to the 
	// tio left corner of the given box.
	int boxIndex;
	// Checks wheter the given row or box is one of the avaliable rows or 
	// columns.
	std::vector<int>::iterator validChecker;

	// Iterates through every column and finds a valid square to place the 
	// squareValue.
	for (int column = 1; column < 10; column++) {
		foundRow = false;
		// While a valid square has not been found.
		while (!foundRow || !foundBox) {
			foundRow = false;
			foundBox = false;
			// Generates a random row value and checks if it is in the vector 
			// of avaliable rows.
			row = avaliableRows[rand() % avaliableRows.size()];
			validChecker = std::find(avaliableRows.begin(), avaliableRows.end(), row);
			if (validChecker != avaliableRows.end()) {
                rowIndex = std::distance(avaliableRows.begin(), validChecker);
				foundRow = true;
			}
		
			box = convertToBox(row, column);
			// Checks if the corresponding box is in the vector of avaliable 
			// boxes.
			validChecker = std::find(avaliableBoxes.begin(), avaliableBoxes.end(), box);
			if (validChecker != avaliableBoxes.end() && board[(row - 1) * 9 + column - 1] == 0) {
                boxIndex = std::distance(avaliableBoxes.begin(), validChecker);
				foundBox = true;
			}
		}
		// Removes the row and box from their respectve avaliable vectors and 
		// sets the square on the Sudoku board to squareValue. 
		avaliableRows.erase(avaliableRows.begin() + rowIndex);
		avaliableBoxes.erase(avaliableBoxes.begin() + boxIndex);
		board[(row - 1) * ROW_SIZE + column - 1] = squareValue;
	}
}

void SudokuGenerator::createPuzzle(SudokuGame &sudokuGame) {
	// Places all of one of the values between 1-9 on the sudoku board and 
	// solves for the rest of the board.
	srand(time(0));
	int squareValue = (rand() % 9) + 1;
    placeValue(sudokuGame.startBoard, squareValue);
	sudokuGame.currentBoard = sudokuGame.startBoard;
    sudokuGame.solveGame();

    sudokuGame.solverMode = false;
    // The index of the value to remove from the Sudoku board.
    int indexToRemove;
    // The value removed from the Sudoku board.
    int removedValue;
    // The number of values removed from the Sudoku board.
    int removedCount = 0;
    std::vector<int> tempBoard = sudokuGame.currentBoard;
    sudokuGame.solvedBoard = tempBoard;

    // While there are more then 30 values left on the board.
    while (removedCount < 51) {
        do {
            indexToRemove = rand() % 81;
            removedValue = sudokuGame.startBoard[indexToRemove];
            if (removedValue != 0) {
                sudokuGame.currentBoard[indexToRemove] = 0;
                sudokuGame.startBoard = sudokuGame.currentBoard;
                tempBoard = sudokuGame.currentBoard;

                // Solve for the baord created by removing the value at the 
                //given index
                sudokuGame.solveGame();
                removedCount++;
                sudokuGame.currentBoard = tempBoard;
                sudokuGame.startBoard = tempBoard;

                // If there is more than one valid solution
                if (sudokuGame.solutionCounter != 1) {
                    sudokuGame.currentBoard[indexToRemove] = removedValue;
                    sudokuGame.startBoard = sudokuGame.currentBoard;
                    removedCount--;

                }
            }
        } while (sudokuGame.solutionCounter == 1);
    }
}

void SudokuGenerator::createPuzzleFile(SudokuGame &sudokuGame) {
    createPuzzle(sudokuGame);
	sudokuGame.saveGame();
}
