#ifndef GAMESERVER_H
#define GAMESERVER_H

#include <QObject>
#include <QWidget>
#include "Game.h"
#include "GameMap.h"
#include "TcpClient.h"
#include "Lib.h"



class GameServer : public QWidget, public Game {
    Q_OBJECT
public:

     GameServer(QWidget *parent, TcpClient *p1, TcpClient *p2);
    ~GameServer();

    // metode
    void play(); // ovo je igranje igre, odnosno premestanje vec postavljenih figura
    void playMove(Player *player, int index, MyGraphicsScene *scene);
    void sendMoveToServer(GAMEMOVE move, int fromIndex, int toIndex);

public slots:
    void readMoveFromServer(GAMEMOVE move);

public:
    FIELDSTATE active;
};

#endif // GAMESERVER_H
