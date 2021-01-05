#include "code/include/Board.h"
#include "code/include/Game.h"
#include "code/include/MainMenu.h"
#include <QApplication>


int main(int argc, char *argv[]) {

    QApplication a(argc, argv);

    Board board;
    MainMenu menu(&board);

    menu.show();
    return a.exec();
}
