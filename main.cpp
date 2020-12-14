#include "board.h"
#include "game.h"
#include "mainmenu.h"
#include <QApplication>


int main(int argc, char * argv[]) {
    // Sluzi za iscrtavanje, iskomentarisano radi testiranja
    QApplication a(argc, argv);

    Board board;
    MainMenu menu(&board);

    menu.show();
    return a.exec();

    /*Board w;
    w.show();
    return a.exec();

        Testiranje prve faze igre
        Player p1(FIELDSTATE::PLAYER_1, std::string("Marija"));
        Player p2(FIELDSTATE::PLAYER_2, std::string("Mr    c"));

        std::cout << p1.getName()<< std::endl;
        Game g = Game(p1, p2);
        g.setup(); //prva faza
        //g.play(); //druga faza
    */
}
