#ifndef SUDOKUPUZZLE_H
#define SUDOKUPUZZLE_H

#include "SudokuGame.h"
#include "SudokuGenerator.h"

#include <QMainWindow>
#include <QLineEdit>
#include <QTimer>
#include <QElapsedTimer>
#include <QIntValidator>

namespace Ui {
class SudokuPuzzle;
}

/*A class to handle the interactions between the the model of the Sudoku game 
  and the UI*/
class SudokuPuzzle : public QMainWindow {
    Q_OBJECT

public:
    explicit SudokuPuzzle(QWidget *parent = nullptr);
    ~SudokuPuzzle();
    // The instance of the sudokuGame model that is being manipulated.   
    SudokuGame sudokuGame;

    // Sets the text of each QLineEdit with the corresponding value from the
    // sudokuGame model. If the square is given at the start of the puzzle it is
    // also coloured blue and set to read only.
    void setBoard();
    
    // Creates a new QTimer and starts both the QTimer and QElapsed Timer. Also
    // sets the starting time to the SudokuGame's puzzleTime value.
    void startClock();
    
    // Reads from the text file with the corresponding fileName and sets the 
    // relevant values of the SudokuGame model.
    //
    // Parameters:
    //  - fileName: The name of the file to read from
    void loadGame(QString fileName);
   
private slots:
    // Creates a new sudokuPuzzle instance and opens a new file explorer. Then 
    // loads the selected text file's parameters into the model of the newly 
    // created SudokuPuzzle instance and closes the current SudokuPuzzle instance.
    void on_LoadButton_clicked();
    
    // Resets the SudokuGame model and restarts the clock.
    void on_ResetButton_clicked();

    // Toggles the SudokuPuzzle between paused and active. While paused, all of 
    // the squares are set to read only mode and the clock is stopped. When the
    // pause button is pressed again the puzzle returns to normal.
    void on_PauseButton_clicked();

    // Shows the solution for the puzzle and prompts the user if they wish to 
    // play another game.
    void on_SolveGame_clicked();

    // Saves the sudokuGame model in it's current form. 
    void on_SaveButton_clicked();

    // Creates a new sudokuPuzzle and randomly generates and new sudokuGame 
    // model. Then closes the current sudokuPuzzle instance and displays the 
    //new instance.
    void on_NewButton_clicked();

    // Updates the time displayed by the clock. 
    void updateTime();

    // Searches for updates in the UI board and makes the neccesary 
    // adujustments to the SudokuGame model. If the puzzle becomes 
    // solved by this change, it asks the user whtheryer they want to play a
    // new puzzle.
    void updateModel();


private:
    Ui::SudokuPuzzle* ui;
    // Another sudokuPuzzle instance used to create new games.
    SudokuPuzzle* sudokuPuzzle;
    // A sudokuGenerator instance used to randomly generate new Sudoku boards.
    SudokuGenerator sudokuGenerator;
    // A timer used to contiously check for updates in the UI.
    QTimer* timer;
    // A clock to measure the amount of time that has passed since starting 
    // the puzzle.
    QElapsedTimer clock;
    // A list of all the QLineEdits which make up the Sudoku board visible to 
    // the user.
    QList<QLineEdit *> sudokuSquares;
    // Represents whether the game is currently paused.
    bool isPaused = false;
    // The amount of time in miliseconds that has passed since beginning the 
    //puzzle.
    qint64 elapsedTime = 0;
    
    // Converts a QLineEdit object to the corresponding index on the SudokuGame
    // model.
    //
    // Parameters:
    //  - square: The QLineEdit which is being referred to
    //
    // Returns:
    //  - The index corresponding to the QLineEdit in the SudokuGame model
    int objectToIndex(QLineEdit* square);
};

#endif // SUDOKUPUZZLE_H
