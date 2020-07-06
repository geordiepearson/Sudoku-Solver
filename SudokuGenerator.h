#ifndef SUDOKUGENERATOR_H_
#define SUDOKUGENERATOR_H_

#include <vector>

class SudokuGenerator {
public:
	void selectSquare(std::vector<int> &board, int squareValue);

private:
	std::vector<int> avaliableRows {1, 2, 3, 4, 5, 6, 7, 8, 9};
	std::vector<int> avaliableBoxes {1, 2, 3, 4, 5, 6, 7, 8, 9};
};

#endif /*SUDOKUGENERATOR_H_*/