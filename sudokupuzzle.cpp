#include "sudokupuzzle.h"
#include "ui_sudokupuzzle.h"
#include "SudokuGame.h"
#include "SudokuSolver.h"
#include <string>
#include <iostream>
#include <QApplication>
#include <QMessageBox>

/*
    Check for win UI

    Sudoku Solver run in separate thread

    disable buttons on solve and win
*/

SudokuPuzzle::SudokuPuzzle(QWidget *parent):
    QMainWindow(parent),
    ui(new Ui::SudokuPuzzle) {
    ui->setupUi(this);

    this->sudokuSquares = (centralWidget()->findChild<QWidget*>("widget"))->findChildren<QLineEdit*>();
    initialiseBoard();
    timer = new QTimer();
    connect(timer, SIGNAL(timeout()), SLOT(updateTime()));
    timer->start(100);
    clock.start();
}

SudokuPuzzle::~SudokuPuzzle() {
    delete ui;
}

int SudokuPuzzle::objectToIndex(QLineEdit* square) {
    int squareIndex;
        if (square->objectName().length() == 7) {
            squareIndex = square->objectName().right(1).toInt();
        } else {
            squareIndex = square->objectName().right(2).toInt();
        }
    return squareIndex;
}

void SudokuPuzzle::initialiseBoard() {
    int squareIndex;
    for (QLineEdit* square: sudokuSquares) {
        square->setValidator(new QRegExpValidator(QRegExp("[1-9]")));
        squareIndex = objectToIndex(square);
        if (sudokuGame.startBoard[squareIndex] != 0) {
            square->setText((QString::fromStdString(std::to_string(sudokuGame.startBoard[squareIndex]))));
            square->setStyleSheet("color:blue");
            square->setReadOnly(true);
        }
        connect(square, SIGNAL(textEdited(const QString&)), SLOT(updateModel()));
    }
    setBoard();
}

void SudokuPuzzle::setBoard() {
    int squareIndex;
    for (QLineEdit* square : sudokuSquares) {
        squareIndex = objectToIndex(square);
        if (sudokuGame.startBoard[squareIndex] == 0) {
        square->setText((QString::fromStdString("")));
        } else {
        square->setText((QString::fromStdString(std::to_string(sudokuGame.currentBoard[squareIndex]))));
        }
    }
}

void SudokuPuzzle::on_ResetButton_clicked() {
    sudokuGame.restartGame();
    setBoard();
    elapsedTime = 0;
    clock.restart();
}

void SudokuPuzzle::on_PauseButton_clicked() {
    if (!isPaused) {
        elapsedTime += clock.elapsed();
        timer->stop();
        centralWidget()->findChild<QPushButton*>("PauseButton")->setText("Resume");
        for (QLineEdit* square : sudokuSquares) {
            square->setReadOnly(true);
        }
    } else {
        timer->start();
        clock.restart();
        centralWidget()->findChild<QPushButton*>("PauseButton")->setText("Pause");

        int squareIndex;
        for (QLineEdit* square : sudokuSquares) {
            squareIndex = objectToIndex(square);
            if (sudokuGame.startBoard[squareIndex] == 0) {
                square->setReadOnly(false);
            }
        }
    }
    isPaused = !isPaused;
}

void SudokuPuzzle::updateTime() {
    qint64 timePassed = clock.elapsed() + elapsedTime;
    int hours = timePassed / 1000 / 60 / 60;
    int minutes = (timePassed / 1000 / 60) - (hours * 60);
    int seconds = (timePassed / 1000) - (minutes * 60);
    QString timeDifference = QString("%1:%2:%3").arg(hours).arg(minutes).arg(seconds);
    centralWidget()->findChild<QLabel*>("TimeLabel")->setText(timeDifference);
}

void SudokuPuzzle::updateModel() {
    QLineEdit* square = qobject_cast<QLineEdit*>(this->sender());
    int squareIndex = objectToIndex(square);
    int squareValue = square->text().toInt();
    sudokuGame.currentBoard[squareIndex] = squareValue;
    
    if (sudokuGame.checkWin()) {
        QMessageBox::StandardButton gameOver;
        gameOver = QMessageBox::question(this, "Puzzle Solved", "Puzzle Solved, start a new puzzle?", QMessageBox::Yes|QMessageBox::No);
        timer->stop();
        // Add logic for new game
        if (gameOver == QMessageBox::No) {
            QApplication::quit();
        }
    }
}

void SudokuPuzzle::on_SolveGame_clicked() {
    timer->stop();
    sudokuGame.solveGame();
    int squareIndex;
    for (QLineEdit* square : sudokuSquares) {
        squareIndex = objectToIndex(square);
        square->setText((QString::fromStdString(std::to_string(sudokuGame.currentBoard[squareIndex]))));
    }
}
