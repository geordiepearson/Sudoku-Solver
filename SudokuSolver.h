#ifndef SUDOKUSOLVE_H_
#define SUDOKUSOLVE_H_

/*A class used to compute the solution of a Sudoku puzzle*/
class SudokuSolver {
private:
	// Indicates whether the puzzle has been solved
	bool isSolved = false;

	// Checks either the given row or column and updates a vector with the 
	// valid values that could be placed into this row or column. This row
	// or column begins at the starting index and extends the specified 
	// number of tiles, downwards for columns and horizontally to the right
	// for rows.
	//
	// Parameters:
	// 	- startingIndex: The index of the Sudoku board to start the row or 
	//	 	column at
	// 	- noSquares: The number of squares the row or column extends
	// 	- validValues: Vector of valid values that could be inserted into 
	//  	the row/column on the board
	//	- searchType: The type of search to conduct (eg. row or column)
	//  - board: The current Sudoku board
	void checkRowColumn(int noTiles, int startingIndex, std::vector<int> 
		&validValues, std::string searchType, std::vector<int> &board);

	// Checks the 3 by 3 box that the given index is within and and updates
	// a vector with the valid values that could be placed into this box.
	//
	// Parameters:
	//	- squareIndex: The index of a square on the Sudoku board. The 3 by 
	//	  3 box that contains this square will be checked for possible 
	//  	valid values 
	//	- validValues: Vector of valid values that could be inserted into 
	//  	the box
	//  - board: The current Sudoku board
	void checkBox(int squareIndex, std::vector<int> &validValues, 
		std::vector<int> &board);

	// Solves for all of the valid Sudoku values that can be placed in the 
	// given square
	//
	// Parameters:
	//	- squareIndex: The index of the square that's values are being 
	//	  solved for
	//	- potentialValues: A vector of potential values that the given 
	//	  square could have
	//  - board: The current Sudoku board
	void solveSquare(int squareIndex, std::vector<int> &potentialValues, 
		std::vector<int> &board);

public:
	// Solves the sudoku board, beginning at the starting index. Solves 
	// using a backtracing algorithm, finding the possible values of the 
	// current square and using those values to recursively search for the
	// possible values of the next square until the solution is reached.
	//
	// Parameters:
	//  - startingIndex: The index on the Sudoku board to start solving 
	// 	  from
	//  - board: The current Sudoku board
	//  - givenIndexes: The indexes of the Sudoku board that are originally 
	//    given in the puzzle
	void solveBoard(int startingIndex, std::vector<int> &board, 
		std::vector<int> &givenIndexes);
};

#endif /*SUDOKUSOLVE_H_*/