#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <cstdlib>
#include "SudokuGenerator.h"
#include <ctime>

void SudokuGenerator::selectSquare(std::vector<int> &board, int squareValue) {
	avaliableRows  = {1, 2, 3, 4, 5, 6, 7, 8, 9};
	avaliableBoxes = {1, 2, 3, 4, 5, 6, 7, 8, 9};
	bool foundRow;
	bool foundBox;
	int row;
	int rowIndex;
	std::vector<int>::iterator rowThing;
	int box;
	int boxIndex;
	std::vector<int>::iterator boxThing;
	
	for (int column = 1; column < 10; column++) {
		foundRow = false;
		while (!foundRow || !foundBox) {
			foundRow = false;
			foundBox = false;
			row = avaliableRows[rand() % avaliableRows.size()];
			rowThing = std::find(avaliableRows.begin(), avaliableRows.end(), row);
			if (rowThing != avaliableRows.end()) {
				rowIndex = std::distance(avaliableRows.begin(), rowThing);
				foundRow = true;
			}
		
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
			
			boxThing = std::find(avaliableBoxes.begin(), avaliableBoxes.end(), box);
			if (boxThing != avaliableBoxes.end() && board[(row - 1) * 9 + column - 1] == 0) {
				boxIndex = std::distance(avaliableBoxes.begin(), boxThing);
				foundBox = true;
			}
		}
		avaliableRows.erase(avaliableRows.begin() + rowIndex);
		avaliableBoxes.erase(avaliableBoxes.begin() + boxIndex);
		board[(row - 1) * 9 + column - 1] = squareValue;
	}
}

