#include "mainmenu.h"
#include "ui_mainmenu.h"
#include "sudokupuzzle.h"
#include "SudokuGenerator.h"

#include <QPushButton>
#include <QFileDialog>
#include <fstream>

MainMenu::MainMenu(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainMenu) {
    ui->setupUi(this);
}

MainMenu::~MainMenu() {
    delete ui;
}

void MainMenu::on_StartButton_clicked() {
    sudokuPuzzle = new SudokuPuzzle();
    sudokuGenerator.createPuzzleFile(sudokuPuzzle->sudokuGame);
    // Sets the sudokuPuzzle window ready to be used
    sudokuPuzzle->setBoard();
    sudokuPuzzle->show();
    sudokuPuzzle->startClock();
    this->destroy();
}


void MainMenu::on_CreateButton_clicked() {

}


void MainMenu::on_LoadButton_clicked() {
    sudokuPuzzle = new SudokuPuzzle();
    // Creates file browser that accepts text files and gets file name
    QFileDialog loadFile(sudokuPuzzle);
    QString fileName = loadFile.getOpenFileName(sudokuPuzzle, tr("Open File"), 
        "/path/to/file/",tr("Text Files (*.txt)"));
    // Loads the given file and sets the sudokuPuzzle window ready to be used
    if (!fileName.isEmpty() && !fileName.isNull()) {
        sudokuPuzzle->loadGame(fileName);
        this->destroy();
    }
}
