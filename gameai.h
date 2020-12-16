#ifndef GAMEAI_H
#define GAMEAI_H

#include "game.h"

#include "gamemap.h"
#include "player.h"
#include "lib.h"

/*
 * Klasa Game
 * sadrzi GameMap (mapa koju je Marija pravila koja sadrzi vektor svih polja)
 *        dva igraca (za sada su oba Player)
 */

class GameAI: public Game{
public:

    GameAI(Player* p1, Player* p2);
    ~GameAI();

    //void playMove(Player& player, int index, QGraphicsScene &scene);

    // ovde dodajem AI funkcije
    void makeSetupMove_AI(Player* player, int i);    // ides u drugu klasu
    void revertSetupMove_AI(Player* player, int i);


    //ai funkcije
    std::pair<int,int> max(int depth);
    std::pair<int,int> min(int depth);

    int             maxDepthAI;
};

#endif // GAMEAI_H
