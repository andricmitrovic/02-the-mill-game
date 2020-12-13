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
    tcp = new TcpClient(FIELDSTATE::PLAYER_1, ui->leName->text());
    // trebalo bi vec server da je pokrenut i da prima jednog igraca
    //board = new Board(this);
    //board->show();
    GameServer *gameServer = new GameServer(*tcp, *new TcpClient(FIELDSTATE::PLAYER_2, QString("br2")));
    ui->laError->setText("Zdravo");
    gameServer->serverTest();


    ui->laError->setText(gameServer->m_p2.getReceivedData());
    //this->hide();
    //
}
