#ifndef SUDOKUGAME_H_
#define SUDOKUGAME_H_

#include <vector>
#include <string>

// The total number of squares of a Sudoku board.
#define BOARD_SIZE 81
// The number of squares in each row of a Sudoku Board.
#define ROW_SIZE 9

/*A class to represent the model of a Sudoku game*/
class SudokuGame {
public:
	// The title of the Sudoku game and the name of the text file when saved.
	std::string title = "Let's Play Sudoku";
	// A model of the original Sudoku puzzle.
    std::vector<int> startBoard = std::vector<int>(BOARD_SIZE);
    // A model of the Sudoku puzzle at the current moment.
    std::vector<int> currentBoard = std::vector<int>(BOARD_SIZE);
    // A model of the Sudoku puzzle when solved.
    std::vector<int> solvedBoard = std::vector<int>(BOARD_SIZE);
	// The current state of the Sudoku game solver with:
	//   - true: solving for the first possible valid solution
	//   - false: solving for every possible valid solution 
	bool solverMode = true;
	// The number of valid solutions that the current Sudoku puzzle has
    int solutionCounter;
	// The amount of time passed since beginning the of the puzzle in 
	// milliseconds.
    int puzzleTime = 0;

	// Restarts the Sudoku game by setting the currentBoard to the startBoard
	void restartGame();

    // Solves the Sudoku game for either the first valid solution or every 
    // valid solution.
	void solveGame();

	// Checks whether the Sudoku game has been solved.
	//
	// returns:
	//  - true if game is solved
	//  - false if game isn't solved
	bool checkWin();

	// Converts the given board to a string representation and writes it to the
	// given file.
	// 
	// Parameters:
	//  - board: The board to convert to a string representation.
	//  - file: The file to write the string representation to.
    void writeBoard(std::vector<int> &board, std::ofstream &file);

	// Navigates to the SudokuPuzzles directory and creates a file containing
	// the string representation of the SudokuGame in the format:
	// 
	// SudokuGame Title
	// Sudoku Game Time
	//
	// SudokuGame Start Board row 1
	// SudokuGame Start Board row 2
	// SudokuGame Start Board row 3
	// SudokuGame Start Board row 4
	// SudokuGame Start Board row 5
	// SudokuGame Start Board row 6
	// SudokuGame Start Board row 7
	// SudokuGame Start Board row 8
	// SudokuGame Start Board row 9
    //
	// SudokuGame Current Board row 1
	// SudokuGame Current Board row 2
	// SudokuGame Current Board row 3
	// SudokuGame Current Board row 4
	// SudokuGame Current Board row 5
	// SudokuGame Current Board row 6
	// SudokuGame Current Board row 7
	// SudokuGame Current Board row 8
	// SudokuGame Current Board row 9
    //
    // SudokuGame Solved Board row 1
	// SudokuGame Solved Board row 2
	// SudokuGame Solved Board row 3
	// SudokuGame Solved Board row 4
	// SudokuGame Solved Board row 5
	// SudokuGame Solved Board row 6
	// SudokuGame Solved Board row 7
	// SudokuGame Solved Board row 8
	// SudokuGame Solved Board row 9
	void saveGame();

	// Reads the given file and sets the title, startBoard, currentBoard, 
	// solvedBoard and puzzleTime based upon the information in the text file. 
	//
	// Parameters:
	//  - file: the text file that is being read from
	void readFile(std::ifstream &file);
};

#endif /*SUDOKUGAME_H_*/
