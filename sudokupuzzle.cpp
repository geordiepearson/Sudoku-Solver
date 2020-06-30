#include "sudokupuzzle.h"
#include "ui_sudokupuzzle.h"
#include "SudokuGame.h"
#include <string>
#include <iostream>
#include <QApplication>

/* Implement DoubleValidator
    digitFilter = new QIntValidator();
    digitFilter->setRange(1, 9);
    QWidget* boardWidget = centralWidget()->findChild<QWidget*>("widget");
    QList<QLineEdit *> childList = boardWidget->findChildren<QLineEdit*>();
    for (QLineEdit* child: childList) {
        child->setValidator(digitFilter);
    }

    Colour of numbers based on given or not + read only mode by default and when unpausing

    Updating the model when text edited

    Check for win

    Sudoku Solver
*/

SudokuPuzzle::SudokuPuzzle(QWidget *parent):
    QMainWindow(parent),
    ui(new Ui::SudokuPuzzle) {
    ui->setupUi(this);
    setBoard();



    timer = new QTimer();
    connect(timer, SIGNAL(timeout()), SLOT(updateTime()));
    timer->start(100);
    clock.start();

}

SudokuPuzzle::~SudokuPuzzle() {
    delete ui;
}

void SudokuPuzzle::setBoard() {
    QWidget* boardWidget = centralWidget()->findChild<QWidget*>("widget");
    QList<QLineEdit *> childList = boardWidget->findChildren<QLineEdit*>();
    int count =0;
    for (QLineEdit* child : childList) {
      if (sudokuGame.startBoard[count] == 0) {
        child->setText((QString::fromStdString("")));
     } else {
        child->setText((QString::fromStdString(std::to_string(sudokuGame.startBoard[count]))));
     }
      count++;
    }
}

void SudokuPuzzle::on_ResetButton_clicked() {
    setBoard();
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
        for (QLineEdit* child : childList) {
            child->setReadOnly(false);
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
