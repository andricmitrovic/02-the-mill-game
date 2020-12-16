#ifndef GAMELOCAL_H
#define GAMELOCAL_H

#include "game.h"

#include "gamemap.h"
#include "player.h"
#include "lib.h"

class GameLocal: public Game {
public:

    GameLocal(Player* p1, Player* p2);
    ~GameLocal();

    // TODO playgame

private:
    FIELDSTATE      winner;
    QString         message;

};

#endif // GAMELOCAL_H
