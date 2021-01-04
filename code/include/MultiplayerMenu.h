#ifndef MULTIPLAYERMENU_H
#define MULTIPLAYERMENU_H

#include <QMainWindow>
#include "Board.h"
#include "GameServer.h"
#include "TcpServer.h"

namespace Ui {
class MultiplayerMenu;
}

class MultiplayerMenu : public QMainWindow
{
    Q_OBJECT

public:
    explicit MultiplayerMenu(QWidget *parent = nullptr, GAMEMODE mode=GAMEMODE::AI);
    ~MultiplayerMenu();

private slots:
    void on_connectBtn_clicked();
    void on_btnBackMultiplayer_clicked();


private:
    Ui::MultiplayerMenu *ui;
    GAMEMODE mode;
    Board *board;
    TcpServer *server;

signals:
    void back();
};

#endif // MULTIPLAYERMENU_H
