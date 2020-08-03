#ifndef SUDOKUCREATOR_H
#define SUDOKUCREATOR_H

#include <QMainWindow>

#include "sudokupuzzle.h"
#include "mainmenu.h"


class MainMenu;

namespace Ui {
class SudokuCreator;
}

/*A class to handle the creation of Sudoku Puzzles by the user*/
class SudokuCreator : public QMainWindow {
    Q_OBJECT

public:
    explicit SudokuCreator(QWidget *parent = nullptr);
    ~SudokuCreator();

private slots:
    // Resets the Sudoku board interface to show all empty squares.
    void on_ResetButton_clicked();

    // Checks whether the current Sudoku puzzle displayed is valid. For a 
    // puzzle to be valid it must have exactly one solution. Creates a
    // message box informing the user whether the puzzle is valid an returns a
    // boolean indicating whether the puzzle is valid.
    //
    // Returns:
    //  - true if the puzzle is valid, false otherwise
    bool on_CheckButton_clicked();

    // Checks if the current puzzle is valid and if it is, solves the puzzle
    // and saves it to a text file.
    void on_SaveButton_clicked();

    // Closes the current SudokuCreator window and opens a new MainMenu window.  
    void on_ExitButton_clicked();

private:
    Ui::SudokuCreator *ui;
    // A list of all the QLineEdits which make up the Sudoku board visible to
    // the user.
    QList<QLineEdit *> sudokuSquares;
    // The instance of the sudokuGame model that is being manipulated.
    SudokuGame sudokuGame;
    MainMenu* mainMenu;

    // Converts a QLineEdit object to the corresponding index on the SudokuGame
    // model.
    //
    // Parameters:
    //  - square: The QLineEdit which is being referred to
    //
    // Returns:
    //  - The index corresponding to the QLineEdit in the SudokuGame model
    int objectToIndex(QLineEdit* square);

    // Takes the Sudoku board created by the user and updates the SudokuGame 
    // model board based on the given values.
    void createModel();
};

#endif // SUDOKUCREATOR_H
