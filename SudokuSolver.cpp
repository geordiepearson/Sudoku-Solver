#include <iostream>
#include <algorithm>
#include <cmath>
#include <string>
#include <vector>
#include "SudokuSolver.h"
#include "SudokuGame.h"
	
void SudokuSolver::checkRowColumn(int noTiles, int startingIndex, 
	std::vector<int> &validValues, std::string searchType,
	std::vector<int> &board) {
	// Stores the number of times a specfic value occurs in a row or 
	// column
	int valueCount;
	// The maximum index of the selected row or column
	int maximumIndex;
	// The value needed to get from one square of the row or column to 
	// the next
	int incrementValue;

	// Sets the neccesary values for searching rows and columns
	if (searchType.compare("Row") == 0) {
		maximumIndex = startingIndex + noTiles;
		incrementValue = 1;
	} else if (searchType.compare("Col") == 0) {
		maximumIndex = 8 * noTiles + startingIndex + 1;
		incrementValue = ROW_SIZE;
	}
			
	// For each value a Sudoku square can take, count how many times it
	// occurs in the row/column and if it is 0, add it to the array of 
	// valid values
	for (int sudokuValue = 1; sudokuValue < 10; sudokuValue++) {
		valueCount = 0;
		for (int index = startingIndex; index < maximumIndex; index += 
			incrementValue) {
			if (board[index] == sudokuValue) {
				valueCount++;
			} 
		}
		if (valueCount == 0) {
			validValues.push_back(sudokuValue);
		}
	}
}

void SudokuSolver::checkBox(int squareIndex, std::vector<int> &validValues, 
	std::vector<int> &board) {
	// Arrays to store the resulting valid values for each row within 
	// a box
	std::vector<int> validBoxValuesRow1;
	std::vector<int> validBoxValuesRow2;
	std::vector<int> validBoxValuesRow3;
	// The index of the top left corner of the box
	int boxStartingIndex;

	// Gets the index of the top left corner of the box that the given 
	// square index is in
	if (squareIndex % ROW_SIZE < 3) {
		if (squareIndex < 21) {
			boxStartingIndex = 0;
		} else if (squareIndex < 48) {
			boxStartingIndex = 27;
		} else if (squareIndex < 75) {
			boxStartingIndex = 54;
		}
	} else if (squareIndex % ROW_SIZE < 6) {
		if (squareIndex < 24) {
			boxStartingIndex = 3;
		} else if (squareIndex < 51) {
			boxStartingIndex = 30;
		} else if (squareIndex< 78) {
			boxStartingIndex = 57;
		}
	} else if (squareIndex % ROW_SIZE < 9) {
		if (squareIndex < 27) {
			boxStartingIndex = 6;
		} else if (squareIndex < 54) {
			boxStartingIndex = 33;
		} else if (squareIndex < 81) {
			boxStartingIndex = 60;
		}
	}

	// Computes the valid values for each row of the box
	checkRowColumn(3, boxStartingIndex, validBoxValuesRow1, "Row", board);
	checkRowColumn(3, boxStartingIndex + ROW_SIZE, validBoxValuesRow2, "Row"
		, board);
	checkRowColumn(3, boxStartingIndex + 2 * ROW_SIZE, validBoxValuesRow3, "Row"
		, board);

	// For each possible Sudoku value, checks if the value is in each 
	// row of the box and if it is, add it to the vector of valid values 
	for (int sudokuValue = 1; sudokuValue < 10; sudokuValue++) {
		if (std::find(validBoxValuesRow1.begin(), validBoxValuesRow1.end(), 
			sudokuValue) != validBoxValuesRow1.end() &&
			std::find(validBoxValuesRow2.begin(), validBoxValuesRow2.end(), 
			sudokuValue) != validBoxValuesRow2.end() &&
			std::find(validBoxValuesRow3.begin(), validBoxValuesRow3.end(), 
			sudokuValue) != validBoxValuesRow3.end()) {

			validValues.push_back(sudokuValue);
		}
	}
}

void SudokuSolver::solveSquare(int squareIndex, std::vector<int>
 &potentialValues, std::vector<int> &board) {
	// Vectors to store the resulting valid values for the row, column 
	// and box that the square is a part of
	std::vector<int> validRowValues;
	std::vector<int> validColValues;
	std::vector<int> validBoxValues;
			
	// Gets the row and column of the square from its index
	int row = ROW_SIZE * floor(squareIndex / ROW_SIZE);
	int column = squareIndex % ROW_SIZE;
	// Computes the valid values for the row, column and box that the 
	// square is a part of
	checkRowColumn(ROW_SIZE, row, validRowValues, "Row", board);
	checkRowColumn(ROW_SIZE, column, validColValues, "Col", board);
	checkBox(squareIndex, validBoxValues, board);

	// For each possible Sudoku value, checks if the value is possible 
	// in the row, column and box and if so, adds it to the array of 
	// valid values 
	for (int sudokuValue = 1; sudokuValue < 10; sudokuValue++) {
		if (std::find(validRowValues.begin(), validRowValues.end(), 
			sudokuValue) != validRowValues.end() && 
			std::find(validColValues.begin(), validColValues.end(), 
			sudokuValue) != validColValues.end() && 
			std::find(validBoxValues.begin(), validBoxValues.end(), 
			sudokuValue) != validBoxValues.end()) {

			potentialValues.push_back(sudokuValue);
		}
	}
}

void SudokuSolver::solveBoard(int startingIndex, std::vector<int> &startBoard, 
	std::vector<int> &currentBoard) {
	// Vector to store the valid values a square can take
	std::vector<int> potentialValues;
	if (isSolved == true) {
		return;
	}
	
	// If the square hasn't been solved for, solve for possible values.
	// For each value, try to solve for the next square and repeat this
	// process until the solution is found.
	if (currentBoard[startingIndex] == 0) {
		solveSquare(startingIndex, potentialValues, currentBoard);
		for (int potentialValue: potentialValues) {
			if (isSolved == true) {
				return;
			}
			// If there is a potential valid value, clears all values 
			// past the current square that weren't orginally given.
			if (potentialValue != 0) {
				for (int square = startingIndex; square < BOARD_SIZE; square++) {
					if (startBoard[square] == 0) {
						currentBoard[square] = 0;
					}
				}
				// Sets the current square to the current potential 
				// value and checks if the puzzle is solved
				currentBoard[startingIndex] = potentialValue;
				if (std::find(currentBoard.begin(), currentBoard.end(), 0) == 
					currentBoard.end()) {
					isSolved = true;
					return;
				}
				// Solves the next square of the puzzle with the 
				// current value placed in the square
				solveBoard(startingIndex + 1, startBoard, currentBoard);
			} 
		}
	// Solves for the next square if the current square is already 
	// solved for	
	} else {
		solveBoard(startingIndex + 1, startBoard, currentBoard);
	}
}