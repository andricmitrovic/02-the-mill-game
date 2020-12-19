#include "multiplayermenu.h"
#include "ui_multiplayermenu.h"
#include "tcpclient.h"
#include "gameserver.h"

MultiplayerMenu::MultiplayerMenu(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MultiplayerMenu)
{
    ui->setupUi(this);
}

MultiplayerMenu::~MultiplayerMenu()
{
    delete ui;
}

void MultiplayerMenu::on_connectBtn_clicked()
{
    ui->laError->text().clear();
    if (ui->leName->text().isEmpty()){
        ui->laError->setText("Enter your name!");
        return ;
    }

    server = new TcpServer(this);
    server->show();
    // trebalo bi vec server da je pokrenut i da prima jednog igraca
    board = new Board(this, GAMEMODE::SERVER);
    board->show();
}
