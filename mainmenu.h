#ifndef MAINMENU_H
#define MAINMENU_H

#include <QMainWindow>
#include "sudokupuzzle.h"
QT_BEGIN_NAMESPACE
namespace Ui { class MainMenu; }
QT_END_NAMESPACE

/*A class to to handle the UI and interactions by the user with the applications
 main menu */
class MainMenu : public QMainWindow {
    Q_OBJECT

public:
    MainMenu(QWidget *parent = nullptr);
    ~MainMenu();

private slots:
    // Closes the current window and creates and opens a Sudoku puzzle window
    void on_StartButton_clicked();
    // Closes the current window and creates and opens a new Sudoku builder 
    // window
    void on_CreateButton_clicked();
    // Opens a file explorer ... 
    void on_LoadButton_clicked();

private:
    Ui::MainMenu *ui;
    SudokuPuzzle* sudokuPuzzle;
};
#endif // MAINMENU_H
