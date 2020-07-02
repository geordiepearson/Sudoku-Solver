#include "sudokupuzzle.h"
#include "ui_sudokupuzzle.h"
#include "SudokuGame.h"
#include "SudokuSolver.h"
#include <string>
#include <iostream>
#include <QApplication>

/*
    Check for win UI

    Sudoku Solver run in separate thread

    disable buttons on solve and win
*/

SudokuPuzzle::SudokuPuzzle(QWidget *parent):
    QMainWindow(parent),
    ui(new Ui::SudokuPuzzle) {
    ui->setupUi(this);

    QWidget* boardWidget = centralWidget()->findChild<QWidget*>("widget");
    QList<QLineEdit *> childList = boardWidget->findChildren<QLineEdit*>();

    initialiseBoard(childList);

    timer = new QTimer();
    connect(timer, SIGNAL(timeout()), SLOT(updateTime()));
    timer->start(100);
    clock.start();
}

SudokuPuzzle::~SudokuPuzzle() {
    delete ui;
}

void SudokuPuzzle::initialiseBoard(QList<QLineEdit *> childList) {
    for (QLineEdit* child: childList) {
        child->setValidator(new QRegExpValidator(QRegExp("[1-9]")));
        int square;
        if (child->objectName().length() == 7) {
            square = child->objectName().right(1).toInt();
        } else {
            square = child->objectName().right(2).toInt();
        }

        if (sudokuGame.startBoard[square] != 0) {
            child->setText((QString::fromStdString(std::to_string(sudokuGame.startBoard[square]))));
            child->setStyleSheet("color:blue");
            child->setReadOnly(true);
        }
        connect(child, SIGNAL(textEdited(const QString&)), SLOT(updateModel()));

    }
    resetBoard(childList);
}

void SudokuPuzzle::resetBoard(QList<QLineEdit *> childList) {
    for (QLineEdit* child : childList) {
        int square;
        if (child->objectName().length() == 7) {
            square = child->objectName().right(1).toInt();
        } else {
            square = child->objectName().right(2).toInt();
        }

      if (sudokuGame.startBoard[square] == 0) {
        child->setText((QString::fromStdString("")));
      } else {
        child->setText((QString::fromStdString(std::to_string(sudokuGame.currentBoard[square]))));
      }
    }
}

void SudokuPuzzle::on_ResetButton_clicked() {
    QWidget* boardWidget = centralWidget()->findChild<QWidget*>("widget");
    QList<QLineEdit *> childList = boardWidget->findChildren<QLineEdit*>();

    sudokuGame.restartGame();
    resetBoard(childList);
}

void SudokuPuzzle::on_PauseButton_clicked() {
    QWidget* boardWidget = centralWidget()->findChild<QWidget*>("widget");
    QList<QLineEdit *> childList = boardWidget->findChildren<QLineEdit*>();

    if (!isPaused) {
        elapsedTime += clock.elapsed();
        timer->stop();
        centralWidget()->findChild<QPushButton*>("PauseButton")->setText("Resume");
        for (QLineEdit* child : childList) {
            child->setReadOnly(true);
        }
    } else {
        timer->start();
        clock.start();
        centralWidget()->findChild<QPushButton*>("PauseButton")->setText("Pause");
        int count = 0;
        for (QLineEdit* child : childList) {
            if (sudokuGame.startBoard[count] == 0) {
                child->setReadOnly(false);
            }
            count++;
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
    QLineEdit* squareObject = qobject_cast<QLineEdit*>(this->sender());
    if (squareObject->objectName().length() == 7) {
        QChar square = squareObject->objectName()[6];
        int squareValue = squareObject->text().toInt();
        sudokuGame.currentBoard[square.digitValue()] = squareValue;
    } else {
        QString square = squareObject->objectName().right(2);
        int squareValue = squareObject->text().toInt();
        sudokuGame.currentBoard[square.toInt()] = squareValue;
    }
    if (sudokuGame.checkWin()) {
        std::cout << "u did it";
        timer->stop();
    }
}

void SudokuPuzzle::on_SolveGame_clicked() {
    timer->stop();
    sudokuGame.solveGame();
    QWidget* boardWidget = centralWidget()->findChild<QWidget*>("widget");
    QList<QLineEdit *> childList = boardWidget->findChildren<QLineEdit*>();

    for (QLineEdit* child : childList) {
        int square;
        if (child->objectName().length() == 7) {
            square = child->objectName().right(1).toInt();
        } else {
            square = child->objectName().right(2).toInt();
        }

        child->setText((QString::fromStdString(std::to_string(sudokuGame.currentBoard[square]))));
    }
}
