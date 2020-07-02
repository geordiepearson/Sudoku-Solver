#include "mainmenu.h"
#include "ui_mainmenu.h"
#include "sudokupuzzle.h"
#include <QPushButton>
#include <QFileDialog>

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
    sudokuPuzzle->show();
    this->close();
}


void MainMenu::on_CreateButton_clicked() {
	
}


void MainMenu::on_LoadButton_clicked() {
    QFileDialog::getOpenFileNames(this, tr("Open File"), "/path/to/file/", 
    	tr("Text Files (*.txt)"));
}
