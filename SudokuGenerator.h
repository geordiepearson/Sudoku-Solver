#ifndef SUDOKUGENERATOR_H_
#define SUDOKUGENERATOR_H_

#include "sudokuGame.h"

#include <vector>

/*A class that generates random, valid Sudoku puzzles*/
class SudokuGenerator {
public:	
	// Creates a Sudoku puzzle and alters the given sudokuGame to match the 
	// generated puzzle. Then saves the sudokuGame to a text file.
	//
	// Parameters: 
	//  - sudokuGame: the sudokuGame instance to generate the new puzzle for
    void createPuzzleFile(SudokuGame &sudokuGame);
private:
	// Converts the given row and column to the corresponding box on the
	// Sudoku board.
	int convertToBox(int row, int column);

	// Places the given squareValue in 9 random places on the given board that
	// follow valid sudoku rules.
	//
	// Parameters:
	//  - board: The Sudoku board the values are randomly placed on
	//  - value: The Sudoku value between 1 and 9 that is placed on the board
	void placeValue(std::vector<int> &board, int squareValue);
	
	// Solves the given Sudoku game and continonusly removes the value from a 
	// random square until more than one solution exists, thus creating a valid 
	// Sudoku puzzle.
	// 
	// Parameters:
	//  - sudokuGame: the sudokuGame instance to generate the new puzzle for
	void createPuzzle(SudokuGame &sudokuGame);
};

#endif /*SUDOKUGENERATOR_H_*/
