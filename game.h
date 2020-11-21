#ifndef GAME_H
#define GAME_H

#include "gamemap.h"
#include "humanplayer.h"

enum class GAMESTATE
{
    INIT,
    PLAY
};

/*
 * Klasa Game
 * sadrzi GameMap (mapa koju je Marija pravila koja sadrzi vektor svih polja)
 *        dva igraca (za sada su oba HumanPlayer)
 */

class Game
{
public:
    Game();
    bool checkMills(unsigned index);
    void removeOpponentsPiece();
    void setup(); // ovo je postavljanje figura, tj. prva faza igre
    void play(); // ovo je igranje igre, odnosno premestanje vec postavljenih figura

private:
    GameMap         *gameMap;
    HumanPlayer     m_p1;
    HumanPlayer     m_p2;
    GAMESTATE       gameState;
};

#endif // GAME_H
