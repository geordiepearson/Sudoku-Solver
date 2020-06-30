#ifndef SUDOKUPUZZLE_H
#define SUDOKUPUZZLE_H
#include <QMainWindow>
#include <QLineEdit>
#include <SudokuGame.h>
#include <QTimer>
#include <QElapsedTimer>
#include <QIntValidator>

namespace Ui {
class SudokuPuzzle;
}

class SudokuPuzzle : public QMainWindow {
    Q_OBJECT

public:
    explicit SudokuPuzzle(QWidget *parent = nullptr);
    ~SudokuPuzzle();

private slots:
    void on_ResetButton_clicked();

    void on_PauseButton_clicked();

    void updateTime();

private:
    Ui::SudokuPuzzle* ui;
    SudokuGame sudokuGame;
    QTimer* timer;
    QElapsedTimer clock;
    bool isPaused = false;
    qint64 elapsedTime = 0;
    QIntValidator* digitFilter;
    void setBoard();


};

#endif // SUDOKUPUZZLE_H