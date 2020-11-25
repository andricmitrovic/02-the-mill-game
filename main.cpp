#include "board.h"
#include "game.h"
#include <QApplication>


int main(int argc, char *argv[])
{
    // Sluzi za iscrtavanje, iskomentarisano radi testiranja
    QApplication a(argc, argv);
    Board w;
    w.show();
    return a.exec();

  // Testiranje prve faze igre
/*    HumanPlayer p1(FIELDSTATE::PLAYER_1, std::string("Marija"));
    HumanPlayer p2(FIELDSTATE::PLAYER_2, std::string("Mrc"));

    std::cout << p1.getName()<< std::endl;
    Game g = Game(p1, p2);
    g.setup(); //prva faza
    g.play(); //druga faza
*/

}

