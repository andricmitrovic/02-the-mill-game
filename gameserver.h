#ifndef GAMESERVER_H
#define GAMESERVER_H

#include "game.h"
#include "gamemap.h"
#include "tcpclient.h"
#include "lib.h"

class GameServer : public Game {
public:

    GameServer(TcpClient *p1, TcpClient *p2);
    ~GameServer();

    // metode
    void serverTest();
    void play(); // ovo je igranje igre, odnosno premestanje vec postavljenih figura
    void playMove(Player *player, int index, QGraphicsScene &scene);
    void getMoveFromServer();
    void sendMoveToServer(GAMEMOVE move, int fromIndex, int toIndex);
};

#endif // GAMESERVER_H
