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

    void playSetupMoveAI(QGraphicsScene &scene);
    void playMovingMoveAI(QGraphicsScene &scene);
    void playMillAI(QGraphicsScene &scene);

    // Helper functions
    bool turnAI();
    Player* getPlayerAI();
    Player* getPlayerHuman();
    FIELDSTATE getHumanFieldstate();

    // Minimax phase 1
    std::pair<int,int> maxSetup(int depth, int alfa, int beta);
    std::pair<int,int> minSetup(int depth, int alfa, int beta);

    void makeSetupMoveAI(Player* player, int i);
    void revertSetupMoveAI(Player* player, int i);

    // Minimax phase 2
    std::tuple<int,int,int> maxPlay(int depth, int alfa, int beta);
    std::tuple<int,int,int> minPlay(int depth, int alfa, int beta);

    void makePlayMoveAI(Player* player, int from, int to);
    void revertPlayMoveAI(Player* player, int from, int to);



private:
    int             maxDepthAI;
    FIELDSTATE      playerAI;
};

#endif // GAMEAI_H
