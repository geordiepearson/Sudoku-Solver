#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <cstdlib>
#include "SudokuGenerator.h"
#include <ctime>
/*
void SudokuGenerator::selectSquare(std::vector<int> &board) {
	srand(time(0));
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
			row = avaliableRows[(rand() % (avaliableRows.size() - 1))];
			rowThing = std::find(avaliableRows.begin(), avaliableRows.end(), row);
			if (rowThing != avaliableRows.end()) {
				rowIndex = std::distance(avaliableRows.begin(), rowThing);
				foundRow = true;
			}
		
			if (column < 4) {
				if (row + 1 < 4) {
					box = 1;
				} else if (row + 1 < 7) {
					box = 4;
				} else if (row + 1 < 10) {
					box = 7;
				}
			} else if (column < 7) {
				if (row + 1 < 4) {
					box = 2;
				} else if (row + 1 < 7) {
					box = 5;
				} else if (row + 1 < 10) {
					box = 8;
				}
			} else if (column < 10) {
				if (row + 1 < 4) {
					box = 3;
				} else if (row + 1 < 7) {
					box = 6;
				} else if (row + 1 < 10) {
				box = 9;
				}
			}
			
			boxThing = std::find(avaliableBoxes.begin(), avaliableBoxes.end(), box);
			if (boxThing != avaliableBoxes.end()) {
				boxIndex = std::distance(avaliableBoxes.end(), boxThing);
				foundBox = true;
			}
			std::cout << " (" << column << " " << row + 1 << " " << box << ") ";
		}
		std::cout << "yeet";
		avaliableRows.erase(avaliableRows.begin() + rowIndex);
		avaliableBoxes.erase(avaliableBoxes.begin() + rowIndex);
		//board[(row - 1) * 8 + column] = 1;
	}
}
*/
