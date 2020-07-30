#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include "windows.h"
#include "SudokuSolver.h"
#include "SudokuGame.h"
#include "SudokuGenerator.h"

#include <locale>
#include <codecvt>

void SudokuGame::printBoard() {
	for (int i = 0; i < 81; i++) {
		if (i % 9 == 0 && i != 0) {
			std::cout << "\n";
		}
        std::cout << currentBoard[i] << " ";
	}
}

void SudokuGame::restartGame() {
	currentBoard = startBoard;
}

void SudokuGame::solveGame() {
	SudokuSolver sudokusolver;
	counter = 0;
	sudokusolver.solveBoard(0, startBoard, currentBoard, counter, gameMode);
}

bool SudokuGame::checkWin() {
    if (std::find(currentBoard.begin(), currentBoard.end(), 0) ==
					currentBoard.end()) {
		return true;
	}
	return false;
}

void SudokuGame::saveGame() {
    TCHAR buffer[MAX_PATH] = { 0 };
    GetModuleFileName(NULL, buffer, MAX_PATH);
    std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
    std::string directory = converter.to_bytes(buffer);
    std::size_t pos = directory.find("SudokuApplication");
    directory = directory.substr(0, pos + 17);
    std::string fileName = this->title + ".txt";
    directory = directory + "/SudokuPuzzles/" + fileName;

    std::ofstream puzzleFile(directory);

    puzzleFile << this->title << "\n";
    puzzleFile << this->time << "\n\n";
	for (int i = 0; i < 81; i++) {
		if (i % 9 == 0 && i != 0) {
			puzzleFile << "\n";
		}
		puzzleFile << this->startBoard[i] << " ";
	}

	puzzleFile << "\n\n";

	for (int i = 0; i < 81; i++) {
		if (i % 9 == 0 && i != 0) {
			puzzleFile << "\n";
		}
		puzzleFile << this->currentBoard[i] << " ";
	}

	puzzleFile << "\n\n";

	for (int i = 0; i < 81; i++) {
		if (i % 9 == 0 && i != 0) {
			puzzleFile << "\n";
		}
		puzzleFile << this->solvedBoard[i] << " ";
	}
    puzzleFile.close();
}

void SudokuGame::loadGame() {
	return;
}
