#ifndef SUDOKUGENERATOR_H_
#define SUDOKUGENERATOR_H_

#include <vector>
#include "sudokuGame.h"

class SudokuGenerator {
public:
	void selectSquare(std::vector<int> &board, int squareValue);
	void createPuzzle(SudokuGame &sudokuGame);
    void createPuzzleFile(SudokuGame &sudokuGame);
private:
	std::vector<int> avaliableRows {1, 2, 3, 4, 5, 6, 7, 8, 9};
	std::vector<int> avaliableBoxes {1, 2, 3, 4, 5, 6, 7, 8, 9};
};

#endif /*SUDOKUGENERATOR_H_*/
