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
    int heuristicSetup(FIELDSTATE player);

    // Minimax phase 2
    std::tuple<int,int,int> maxPlay(int depth, int alfa, int beta);
    std::tuple<int,int,int> minPlay(int depth, int alfa, int beta);

    void makePlayMoveAI(Player* player, int from, int to);
    void revertPlayMoveAI(Player* player, int from, int to);



private:
    int             maxDepthPhase1;
    int             maxDepthPhase2;             // todo: moze da bude veci depth kad ima ostane manje piece-ova na boardu
    FIELDSTATE      playerAI;
};

#endif // GAMEAI_H
