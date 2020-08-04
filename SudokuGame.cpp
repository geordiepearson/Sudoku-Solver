#include "windows.h"
#include "SudokuSolver.h"
#include "SudokuGame.h"
#include "SudokuGenerator.h"

#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <locale>
#include <codecvt>

void SudokuGame::restartGame() {
	currentBoard = startBoard;
}

void SudokuGame::solveGame() {
	SudokuSolver sudokusolver;
    solutionCounter = 0;
    sudokusolver.solveBoard(0, startBoard, currentBoard, solvedBoard, 
        solutionCounter, solverMode);
}

bool SudokuGame::checkWin() {
    if (currentBoard == solvedBoard) {
		return true;
	}
	return false;
}

void SudokuGame::writeBoard(std::vector<int> &board, std::ofstream &file) {
	for (int i = 0; i < BOARD_SIZE; i++) {
		if (i % ROW_SIZE == 0 && i != 0) {
			file << "\n";
		}
        file << board[i] << " ";
	}
	file << "\n\n";
}

void SudokuGame::saveGame() {
	// Finds the filepath to the directory called SudokuApplication
    TCHAR buffer[MAX_PATH] = { 0 };
    GetModuleFileName(NULL, buffer, MAX_PATH);
    std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
    std::string directory = converter.to_bytes(buffer);
    std::size_t pos = directory.find("release");

    // Alters the filepath to the directory SudokuPuzzles
    directory = directory.substr(0, pos + 7);
    std::cout << directory << "\n\n";
    std::string fileName = this->title + ".txt";
    directory = directory + "/SudokuPuzzles/" + fileName;
    std::cout << directory << "\n\n";
    // Creates the file in the directory and writes to it
    std::ofstream puzzleFile(directory);
    puzzleFile << this->title << "\n";
    puzzleFile << this->puzzleTime << "\n\n";
    this->writeBoard(startBoard, puzzleFile);
    this->writeBoard(currentBoard, puzzleFile);
    this->writeBoard(solvedBoard, puzzleFile);
    puzzleFile.close();
}

void SudokuGame::readFile(std::ifstream &file) {
	int line = 0;
    int value;
    std::string currentLine;
    while(std::getline(file, currentLine)) {
        if (line == 0) {
            title = currentLine;
        } else if (line == 1) {
            puzzleTime = stoi(currentLine);
        } else if (line > 2 && line < 12) {
            for (int square = 0; square < ROW_SIZE; square++) {
            	// Convert char read from file to int and sets respective 
            	// square of board to that value
                value = (int) currentLine[2 * square] - 48;
                startBoard[square + (line - 3) * ROW_SIZE] = value;
            }
        } else if (line > 12 && line < 22) {
            for (int square = 0; square < ROW_SIZE; square++) {
                // Convert char read from file to int and sets respective 
            	// square of board to that value
                value = (int) currentLine[2 * square] - 48;
                currentBoard[square + (line - 13) * ROW_SIZE] = value;
            }
        } else if (line > 22 && line < 32) {
            for (int square = 0; square < ROW_SIZE; square++) {
                // Convert char read from file to int and sets respective 
            	// square of board to that value
                value = (int) currentLine[2 * square] - 48;
                solvedBoard[square + (line - 23) * ROW_SIZE] = value;
            }
        }
        line++;
    }
}

