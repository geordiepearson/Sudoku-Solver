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

    this->sudokuSquares = (centralWidget()->findChild<QWidget*>("widget"))->findChildren<QLineEdit*>();
    initialiseBoard();
}

SudokuPuzzle::~SudokuPuzzle() {
    delete ui;
}

void SudokuPuzzle::startClock() {
    timer = new QTimer();
    connect(timer, SIGNAL(timeout()), SLOT(updateTime()));
    elapsedTime = this->sudokuGame.time;
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

void SudokuPuzzle::initialiseBoard() {
    for (QLineEdit* square: sudokuSquares) {
        square->setValidator(new QRegExpValidator(QRegExp("[1-9]")));
        connect(square, SIGNAL(textEdited(const QString&)), SLOT(updateModel()));
    }
    setBoard();
}

void SudokuPuzzle::setBoard() {
    int squareIndex;
    for (QLineEdit* square : sudokuSquares) {
        squareIndex = objectToIndex(square);
        if (sudokuGame.currentBoard[squareIndex] == 0) {
            square->setText((QString::fromStdString("")));
        } else {
            square->setText((QString::fromStdString(std::to_string(sudokuGame.currentBoard[squareIndex]))));
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
        gameOver = QMessageBox::question(this, "Puzzle Solved", "Puzzle Solved. Start a new puzzle?", QMessageBox::Yes|QMessageBox::No);
        timer->stop();
        if (gameOver == QMessageBox::No) {
            QApplication::quit();
        } else {
            SudokuPuzzle* sudokuPuzzle = new SudokuPuzzle();
            sudokuGenerator = new SudokuGenerator();
            sudokuGenerator->createPuzzleFile(sudokuPuzzle->sudokuGame);
            delete sudokuGenerator;
            sudokuPuzzle->setBoard();
            sudokuPuzzle->show();
            this->close();
        }
    }
}

void SudokuPuzzle::on_SolveGame_clicked() {
    timer->stop();
    int squareIndex;
    for (QLineEdit* square : sudokuSquares) {
        squareIndex = objectToIndex(square);
        square->setText((QString::fromStdString(std::to_string(sudokuGame.solvedBoard[squareIndex]))));
    }
    QMessageBox::StandardButton gameOver;
    gameOver = QMessageBox::question(this, "Puzzle Solved", "Puzzle Solved. Start a new puzzle?", QMessageBox::Yes|QMessageBox::No);
    timer->stop();

    if (gameOver == QMessageBox::No) {
        QApplication::quit();
    } else {
        SudokuPuzzle* sudokuPuzzle = new SudokuPuzzle();
        sudokuGenerator = new SudokuGenerator();
        sudokuGenerator->createPuzzleFile(sudokuPuzzle->sudokuGame);
        delete sudokuGenerator;
        sudokuPuzzle->setBoard();
        sudokuPuzzle->show();
        sudokuPuzzle->startClock();
        this->close();
    }
}

void SudokuPuzzle::on_SaveButton_clicked() {
    sudokuGame.time = clock.elapsed() + elapsedTime;
    sudokuGame.saveGame();
}

void SudokuPuzzle::loadGame(std::ifstream& puzzleFile) {
    int line = 0;
    std::string currentLine;
    while(std::getline(puzzleFile, currentLine)) {
        if (line == 0) {
            sudokuGame.title = currentLine;
        } else if (line == 1) {
            sudokuGame.time = stoi(currentLine);
        } else if (line > 2 && line < 12) {
            for (int square = 0; square < 9; square++) {
                int value = (int) currentLine[2 * square] - 48;
                sudokuGame.startBoard[square + (line - 3) * 9] = value;
            }
        } else if (line > 12 && line < 22) {
            for (int square = 0; square < 9; square++) {
                int value = (int) currentLine[2 * square] - 48;
                sudokuGame.currentBoard[square + (line - 13) * 9] = value;
            }
        } else if (line > 22 && line < 32) {
            for (int square = 0; square < 9; square++) {
                int value = (int) currentLine[2 * square] - 48;
                sudokuGame.solvedBoard[square + (line - 23) * 9] = value;
            }
        }
        line++;
    }
}

void SudokuPuzzle::on_LoadButton_clicked() {
    elapsedTime += clock.elapsed();
    timer->stop();
    SudokuPuzzle* sudokuPuzzle = new SudokuPuzzle();
    QFileDialog loadFile(sudokuPuzzle);
    QString fileName = loadFile.getOpenFileName(sudokuPuzzle, tr("Open File"), "/path/to/file/",tr("Text Files (*.txt)"));

    std::ifstream puzzleFile(fileName.toStdString());
    sudokuPuzzle->loadGame(puzzleFile);
    sudokuPuzzle->setBoard();
    centralWidget()->findChild<QLabel*>("GameTitle")->setText(QString::fromStdString(sudokuGame.title));
    sudokuPuzzle->show();
    sudokuPuzzle->startClock();
    this->close();
}

void SudokuPuzzle::on_NewButton_clicked() {
    SudokuPuzzle* sudokuPuzzle = new SudokuPuzzle();
    sudokuGenerator = new SudokuGenerator();
    sudokuGenerator->createPuzzleFile(sudokuPuzzle->sudokuGame);
    delete sudokuGenerator;
    sudokuPuzzle->setBoard();
    sudokuPuzzle->show();
    sudokuPuzzle->startClock();
    this->close();
}
