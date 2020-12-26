#ifndef MULTIPLAYERMENU_H
#define MULTIPLAYERMENU_H

#include <QMainWindow>
#include "board.h"
#include "gameserver.h"
#include "tcpserver.h"

namespace Ui {
class MultiplayerMenu;
}

class MultiplayerMenu : public QMainWindow
{
    Q_OBJECT

public:
    explicit MultiplayerMenu(QWidget *parent = nullptr);
    ~MultiplayerMenu();

private slots:
    void on_connectBtn_clicked();

private:
    Ui::MultiplayerMenu *ui;
    Board *board;
    TcpServer *server;
};

#endif // MULTIPLAYERMENU_H
