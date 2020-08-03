#include "sudokupuzzle.h"
#include "ui_sudokupuzzle.h"
#include "SudokuGame.h"
#include "SudokuGenerator.h"

#include <string>
#include <iostream>
#include <fstream>
#include <QApplication>
#include <QMessageBox>
#include <QFile>
#include <QTextStream>
#include <QDir>
#include <QFileDialog>


SudokuPuzzle::SudokuPuzzle(QWidget *parent):
    QMainWindow(parent),
    ui(new Ui::SudokuPuzzle) {
    ui->setupUi(this);

    sudokuSquares = (centralWidget()->findChild<QWidget*>("widget"))->
      findChildren<QLineEdit*>();
    // Sets the validator, signals and slot for every QLineEdit.  
    for (QLineEdit* square: sudokuSquares) {
        square->setValidator(new QRegExpValidator(QRegExp("[1-9]")));
        connect(square, SIGNAL(textEdited(const QString&)), SLOT(updateModel()));
    }
    setBoard();
}

SudokuPuzzle::~SudokuPuzzle() {
    delete ui;
}

void SudokuPuzzle::startClock() {
    timer = new QTimer();
    connect(timer, SIGNAL(timeout()), SLOT(updateTime()));
    // Sets starting time.
    elapsedTime = this->sudokuGame.puzzleTime;
    timer->start(100);
    clock.start();
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

void SudokuPuzzle::setBoard() {
    int squareIndex;
    for (QLineEdit* square : sudokuSquares) {
        squareIndex = objectToIndex(square);
        if (sudokuGame.currentBoard[squareIndex] == 0) {
            square->setText((QString::fromStdString("")));
        } else {
            square->setText((QString::fromStdString(std::to_string
                (sudokuGame.currentBoard[squareIndex]))));
            // Checks whether the square is given in the puzzle.
            if (sudokuGame.startBoard[squareIndex] != 0) {
                square->setStyleSheet("color:blue");
                square->setReadOnly(true);
            }
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
        centralWidget()->findChild<QPushButton*>("PauseButton")->
          setText("Resume");
        for (QLineEdit* square : sudokuSquares) {
            square->setReadOnly(true);
        }
    } else {
        timer->start();
        clock.restart();
        centralWidget()->findChild<QPushButton*>("PauseButton")->
          setText("Pause");

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
    // Converts milliseconds into hours:minutes:seconds.
    int hours = timePassed / 1000 / 60 / 60;
    int minutes = (timePassed / 1000 / 60) - (hours * 60);
    int seconds = (timePassed / 1000) - (minutes * 60);
    QString timeDifference = QString("%1:%2:%3").arg(hours).arg(minutes).
      arg(seconds);
    centralWidget()->findChild<QLabel*>("TimeLabel")->setText(timeDifference);
}

void SudokuPuzzle::updateModel() {
    // Gets the QLineEdit that sent the signal and updates the corresponding 
    // index on the SudokuGameb model.
    QLineEdit* square = qobject_cast<QLineEdit*>(this->sender());
    int squareIndex = objectToIndex(square);
    int squareValue = square->text().toInt();
    sudokuGame.currentBoard[squareIndex] = squareValue;
    
    // If the game is over, create a QMessageBox that allows the user to play 
    // again or quit.
    if (sudokuGame.checkWin()) {
        QMessageBox::StandardButton gameOver;
        gameOver = QMessageBox::question(this, "Puzzle Solved","Puzzle Solved."
          "Start a new puzzle?", QMessageBox::Yes|QMessageBox::No);
        timer->stop();
        if (gameOver == QMessageBox::No) {
            QApplication::quit();
        } else {
            on_NewButton_clicked();
        }
    }
}

void SudokuPuzzle::on_SolveGame_clicked() {
    timer->stop();
    int squareIndex;
    for (QLineEdit* square : sudokuSquares) {
        squareIndex = objectToIndex(square);
        square->setText((QString::fromStdString(std::to_string(sudokuGame.
            solvedBoard[squareIndex]))));
    }
    QMessageBox::StandardButton gameOver;
    gameOver = QMessageBox::question(this, "Puzzle Solved", "Puzzle Solved. "
      "Start a new puzzle?", QMessageBox::Yes|QMessageBox::No);
    timer->stop();

    if (gameOver == QMessageBox::No) {
        QApplication::quit();
    } else {
        on_NewButton_clicked();
    }
}

void SudokuPuzzle::loadGame(QString fileName) {
    std::ifstream puzzleFile(fileName.toStdString());
    this->sudokuGame.readFile(puzzleFile);
    this->setBoard();
    this->centralWidget()->findChild<QLabel*>("GameTitle")->setText
      (QString::fromStdString(this->sudokuGame.title));
    this->show();
    this->startClock();
}

void SudokuPuzzle::on_SaveButton_clicked() {
    sudokuGame.puzzleTime = clock.elapsed() + elapsedTime;
    sudokuGame.saveGame();
}

void SudokuPuzzle::on_LoadButton_clicked() {
    elapsedTime += clock.elapsed();
    timer->stop();
    sudokuPuzzle = new SudokuPuzzle();
    QFileDialog loadFile(this);
    QString fileName = loadFile.getOpenFileName(this, tr("Open File"), 
        "/path/to/file/",tr("Text Files (*.txt)"));
    
    if (!fileName.isEmpty() && !fileName.isNull()) {
        sudokuPuzzle->loadGame(fileName);
        this->close();
    } else {
        timer->start();
        clock.restart();
    }
}

void SudokuPuzzle::on_NewButton_clicked() {
    sudokuPuzzle = new SudokuPuzzle();
    sudokuGenerator.createPuzzleFile(sudokuPuzzle->sudokuGame);
    sudokuPuzzle->setBoard();
    sudokuPuzzle->show();
    sudokuPuzzle->startClock();
    this->close();
}
