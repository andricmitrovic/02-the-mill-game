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

class Game
{
public:

    Game(HumanPlayer& p1, HumanPlayer& p2);
    ~Game();

    bool checkMills(unsigned index) const;
    void removeOpponentsPiece(HumanPlayer& player);
    bool makeSetupMove(HumanPlayer& player);
    bool makeSetupMove_graphical(HumanPlayer &player, unsigned i);
    bool makePlayMove(HumanPlayer& player);
    bool gameOver();
    void setWinner(FIELDSTATE winner);
    bool isValidIndex(int i) const;
    FIELDSTATE getWinner() const;
    bool isValidToRemove(int i, HumanPlayer& player) const;
    bool isValidToMove(int from, int to) const;
    bool isValidToSelect(int i, HumanPlayer& player) const;
    bool isValidToOccupy(int i, HumanPlayer& player) const;

    void setup(); // ovo je postavljanje figura, tj. prva faza igre
    void setup_graphical();
    void check_phase1_end();
    void play(); // ovo je igranje igre, odnosno premestanje vec postavljenih figura

    // seteri i geteri za ovo sve
    HumanPlayer     m_p1;                   // stavio sam public jer mi treba turn metoda nad ovim objektima
    HumanPlayer     m_p2;                   // public
    GameMap         *gameMap;               // i ovo mi treba public
    int             phase1_piece_counter;   // dodao ovo ovde da bi iz boarda znao kada da prekinem prvi deo igre
    GAMESTATE       gameState;

private:  
    FIELDSTATE           winner;
};

#endif // GAME_H