#ifndef MAINMENU_H
#define MAINMENU_H

#include <QMainWindow>
#include "sudokupuzzle.h"
QT_BEGIN_NAMESPACE
namespace Ui { class MainMenu; }
QT_END_NAMESPACE

class MainMenu : public QMainWindow
{
    Q_OBJECT

public:
    MainMenu(QWidget *parent = nullptr);
    ~MainMenu();

private slots:
    void on_CreateButton_clicked();

    void on_StartButton_clicked();

    void on_LoadButton_clicked();

private:
    Ui::MainMenu *ui;
    SudokuPuzzle* sudokuPuzzle;
};
#endif // MAINMENU_H
