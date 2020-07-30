#ifndef SUDOKUPUZZLE_H
#define SUDOKUPUZZLE_H
#include <QMainWindow>
#include <QLineEdit>
#include <SudokuGame.h>
#include <QTimer>
#include <QElapsedTimer>
#include <QIntValidator>
#include "SudokuGenerator.h"

namespace Ui {
class SudokuPuzzle;
}

class SudokuPuzzle : public QMainWindow {
    Q_OBJECT

public:
    explicit SudokuPuzzle(QWidget *parent = nullptr);
    ~SudokuPuzzle();
    void loadGame(std::ifstream& puzzleFile);
    SudokuGame sudokuGame;
    void setBoard();
    void startClock();

public slots:
   void on_LoadButton_clicked();

private slots:
    void on_ResetButton_clicked();

    void on_PauseButton_clicked();

    void updateTime();

    void updateModel();

    void on_SolveGame_clicked();

    void on_SaveButton_clicked();

    void on_NewButton_clicked();

private:
    Ui::SudokuPuzzle* ui;
    SudokuGenerator* sudokuGenerator;
    QTimer* timer;
    QElapsedTimer clock;
    QList<QLineEdit *> sudokuSquares;
    bool isPaused = false;
    qint64 elapsedTime = 0;
    

    void initialiseBoard();
    int objectToIndex(QLineEdit* square);
};

#endif // SUDOKUPUZZLE_H
