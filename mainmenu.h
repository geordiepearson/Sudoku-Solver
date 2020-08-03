#ifndef MAINMENU_H
#define MAINMENU_H

#include <QMainWindow>

#include "sudokupuzzle.h"
#include "SudokuGenerator.h"
#include "sudokucreator.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainMenu; }
QT_END_NAMESPACE

class SudokuCreator;

/*A class to to handle the UI and interactions by the user with the applications
 main menu */
class MainMenu : public QMainWindow {
    Q_OBJECT

public:
    MainMenu(QWidget *parent = nullptr);
    ~MainMenu();

private slots:
    // Generates a random, valid sudoku puzzle. Then closes the current window
    // and opens a SudokuPuzzle window with the newly created puzzle.
    void on_StartButton_clicked();

    // Closes the current window and creates and opens a new Sudoku builder 
    // window.
    void on_CreateButton_clicked();
    
    // Opens a file explorer and creates a Sudoku Puzzle window based on the 
    // selected text file .
    void on_LoadButton_clicked();

private:
    Ui::MainMenu *ui;
    // Declared sudokuPuzzle and sudokuCreator pointers to store dynamically 
    // created instances
    SudokuPuzzle* sudokuPuzzle;
    SudokuCreator* sudokuCreator;
    SudokuGenerator sudokuGenerator;
};
#endif // MAINMENU_H
