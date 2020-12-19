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

    // Phase 1
    void playSetupMoveAI(QGraphicsScene &scene);
    void playMillSetupAI(QGraphicsScene &scene);

    // Phase 2
    void playMovingMoveAI(QGraphicsScene &scene);
    void playMillMovingAI(QGraphicsScene &scene);

    // Helper functions
    bool turnAI();
    Player* getPlayerAI();
    Player* getPlayerHuman();
    FIELDSTATE getHumanFieldstate();

    // Minimax phase 1
    std::pair<int,int> maxSetup(int depth);
    std::pair<int,int> minSetup(int depth);

    void makeSetupMoveAI(Player* player, int i);
    void revertSetupMoveAI(Player* player, int i);

    // Minimax phase 2
    //todo



private:
    int             maxDepthAI;
    FIELDSTATE      playerAI;
};

#endif // GAMEAI_H
