#include "sudokucreator.h"
#include "ui_sudokucreator.h"

#include <QMessageBox>

SudokuCreator::SudokuCreator(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::SudokuCreator) {
    ui->setupUi(this);

    sudokuSquares = (centralWidget()->findChild<QWidget*>("widget"))->
      findChildren<QLineEdit*>();
    // Sets the validator, signals and slot for every QLineEdit.
    for (QLineEdit* square: sudokuSquares) {
        square->setValidator(new QRegExpValidator(QRegExp("[1-9]")));
        square->setStyleSheet("color:blue");
    }
}

SudokuCreator::~SudokuCreator() {
    delete ui;
}

int SudokuCreator::objectToIndex(QLineEdit* square) {
    int squareIndex;
        if (square->objectName().length() == 7) {
            squareIndex = square->objectName().right(1).toInt();
        } else {
            squareIndex = square->objectName().right(2).toInt();
        }
    return squareIndex;
}

void SudokuCreator::on_ResetButton_clicked() {
    for (QLineEdit* square: sudokuSquares) {
        square->setText("");
    }
}

void SudokuCreator::createModel() {
    int squareIndex;
    int squareValue;
    sudokuGame.title = (this->findChild<QTextEdit*>("GameTitle"))->
            toPlainText().toStdString();
    // For every square on the board, update the corresponding square 
    // in the model.
    foreach (QLineEdit* square, sudokuSquares) {
        squareIndex = objectToIndex(square);
        squareValue = square->text().toInt();
        sudokuGame.currentBoard[squareIndex] = squareValue;
    }
    sudokuGame.startBoard = sudokuGame.currentBoard;
}

bool SudokuCreator::on_CheckButton_clicked() {
    createModel();
    sudokuGame.solverMode = NULL;
    sudokuGame.solutionCounter = 0;
    // Checks if the Sudoku puzzle is valid.
    sudokuGame.solveGame();

    if (sudokuGame.solutionCounter == 0) {
        QMessageBox::information(this, tr("Let's Make Sudoku"), 
            tr("Invalid Puzzle, No Valid Solution. Try Again."));
        return false;
    } else if (sudokuGame.solutionCounter > 1) {
        QMessageBox::information(this, tr("Let's Make Sudoku"), 
            tr("Invalid Puzzle, More Than One Valid Solution. Try Again."));
        return false;
    } else {
        QMessageBox::information(this, tr("Let's Make Sudoku"), 
            tr("Valid Sudoku Puzzle"));
        return true;
    }
}

void SudokuCreator::on_SaveButton_clicked() {
    createModel();
    // If the Sudoku puzzle is valid.
    if (this->on_CheckButton_clicked()) {
        sudokuGame.solverMode = true;
        // Updates the SudokuGame's solvedBoard and currentBoard models.
        sudokuGame.solveGame();
        sudokuGame.currentBoard = sudokuGame.startBoard;
        this->sudokuGame.saveGame();
    }

}

void SudokuCreator::on_ExitButton_clicked() {
    mainMenu = new MainMenu();
    mainMenu->show();
    this->close();
}
