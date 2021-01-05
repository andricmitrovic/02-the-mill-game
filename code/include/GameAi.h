#ifndef GAMEAI_H
#define GAMEAI_H

#include "Game.h"

#include "GameMap.h"
#include "Player.h"
#include "Lib.h"

/*
 * Klasa Game
 * sadrzi GameMap (mapa koju je Marija pravila koja sadrzi vektor svih polja)
 *        dva igraca (za sada su oba Player)
 */

class GameAI: public Game{

public:

    GameAI(Player* p1, Player* p2, GAMEMODE gameMode);
    ~GameAI();

    void playMove(Player* player, int index, MyGraphicsScene *scene) override;

    void playSetupMoveAI(MyGraphicsScene *scene);
    void playMovingMoveAI(MyGraphicsScene *scene);
    void playMillAI(MyGraphicsScene *scene);

    // Helper functions
    bool turnAI();
    Player* getPlayerAI();
    Player* getPlayerHuman();
    FIELDSTATE getHumanFieldstate();

    // Minimax phase 1
    std::pair<int,int> maxSetup(int depth, int remainingPieces, int alfa, int beta);
    std::pair<int,int> minSetup(int depth, int remainingPieces, int alfa, int beta);

    void makeSetupMoveAI(Player* player, int i);
    void revertSetupMoveAI(Player* player, int i);
    int heuristicSetup();

    // Minimax phase 2
    std::tuple<int,int,int> maxPlay(int depth, int alfa, int beta);
    std::tuple<int,int,int> minPlay(int depth, int alfa, int beta);

    void makePlayMoveAI(Player* player, int from, int to);
    void revertPlayMoveAI(Player* player, int from, int to);



private:
    // Max depth for minimax algorithm in each phase, best values for a quick AI play
    int             maxDepthPhase1 = 5;
    int             maxDepthPhase2 = 7;

    FIELDSTATE      playerAI;
};

#endif // GAMEAI_H
