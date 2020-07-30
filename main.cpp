#include "mainmenu.h"

#include <QApplication>

int main(int argc, char *argv[]) {
    QApplication Sudoku(argc, argv);
    MainMenu mainMenu;
    mainMenu.show();
    return Sudoku.exec();
}
