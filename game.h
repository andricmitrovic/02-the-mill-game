#ifndef GAME_H
#define GAME_H

#include "gamemap.h"
#include "humanplayer.h"
#include "lib.h"

/*
 * Klasa Game
 * sadrzi GameMap (mapa koju je Marija pravila koja sadrzi vektor svih polja)
 *        dva igraca (za sada su oba HumanPlayer)
 */

class Game {
public:

    Game(HumanPlayer& p1, HumanPlayer& p2);
    ~Game();

    // metode
    void play(); // ovo je igranje igre, odnosno premestanje vec postavljenih figura
    void setup(); // ovo je postavljanje figura, tj. prva faza igre
    void setup_graphical();

    void changeTurn();
    bool makePlayMove(HumanPlayer& player);
    bool makeSetupMove(HumanPlayer& player);
    void playMove(HumanPlayer& player, int index, QGraphicsScene &scene);
    void removeOpponentsPiece(HumanPlayer& player);

    bool makeSetupMove_graphical(HumanPlayer &player, unsigned i, QGraphicsScene &scene);
    bool removeOpponentsPiece_graphic(HumanPlayer& player, unsigned index);
    bool makePlayMove_graphical(HumanPlayer &player, unsigned moveFrom, unsigned moveTo);

    // metodi za proveru stanje igre
    bool gameOver();
    bool checkPhase1End();
    bool checkMills(unsigned index) const;

    //provera indeks

    bool isValidIndex(int i) const;
    bool isValidToMove(int from, int to) const;
    bool isValidToRemove(int i, HumanPlayer& player);
    bool isValidToSelect(int i, HumanPlayer& player) const;
    bool isValidToOccupy(int i, HumanPlayer& player) const;

    // getteri
    QString getMessage() const;
    FIELDSTATE getWinner() const;
    HumanPlayer &getCurrentPlayer();

    // setteri
    void setWinner(FIELDSTATE winner);
    void setMessage(const std::string &msg);

    // seteri i geteri za ovo sve
    GameMap         *gameMap;               // i ovo mi treba public
    HumanPlayer     m_p1;                   // stavio sam public jer mi treba turn metoda nad ovim objektima
    HumanPlayer     m_p2;                   // public
    int             phase1_piece_counter;   // dodao ovo ovde da bi iz boarda znao kada da prekinem prvi deo igre
    GAMESTATE       gameState;
    bool            mill_occured;
    int             moveFrom;
    int             boardPieces;



private:  
    FIELDSTATE      winner;
    QString         message;

};

#endif // GAME_H
