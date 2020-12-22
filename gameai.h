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

    void playMove(Player* player, int index, QGraphicsScene &scene) override;

    // AI funkcije
    bool turnAI();
    void makeSetupMove_AI(Player* player, int i);    // ides u drugu klasu
    void revertSetupMove_AI(Player* player, int i);

    std::pair<int,int> max(int depth);
    std::pair<int,int> min(int depth);

    // TODO: obrisati?: cak se i ne koriste van klase pa nisu potrebni i ne menjaju se
    // geteri
    int        getMaxDepthAI();
    FIELDSTATE getPlayerAI();
    // seteri
    void       setMaxDepthAI(int val);
    void       setPlayerAI(FIELDSTATE val);

private:
    int             maxDepthAI;
    FIELDSTATE      playerAI;
};

#endif // GAMEAI_H
