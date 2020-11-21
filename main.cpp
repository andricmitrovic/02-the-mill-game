#include "board.h"
#include "game.h"

#include <QApplication>


int main(int argc, char *argv[])
{
    // Sluzi za iscrtavanje, iskomentarisano radi testiranja
//    QApplication a(argc, argv);
//    Board w;
//    w.show();
//    return a.exec();

  // Testiranje prve faze igre
    const HumanPlayer p1(VALUE::PLAYER_1);
    const HumanPlayer p2(VALUE::PLAYER_2);

    Game g = Game();
    g.setup(); //prva faza
    //g.play(); //druga faza

}

