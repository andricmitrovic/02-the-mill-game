#include "code/include/MultiplayerMenu.h"
#include <ui_multiplayermenu.h>
#include "code/include/TcpClient.h"
#include "code/include/GameServer.h"

MultiplayerMenu::MultiplayerMenu(QWidget *parent, GAMEMODE mode) :
    QMainWindow(parent),
    ui(new Ui::MultiplayerMenu),
    mode(mode)
{
    ui->setupUi(this);
    this->server = nullptr;
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

    if (mode == GAMEMODE::SERVER)
        server = new TcpServer();

    board = new Board(this, mode, ui->leName->text());
    board->show();
    this->hide();


}
