#include "mainmenu.h"
#include "ui_mainmenu.h"

MainMenu::MainMenu(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainMenu)
{
    ui->setupUi(this);
}

MainMenu::~MainMenu()
{
    delete ui;
}

void MainMenu::on_localPlayBtn_clicked()
{
    board = new Board(this);
    board->show();
    this->hide();
}

void MainMenu::on_serverPlayBtn_clicked()
{
    mp_menu = new MultiplayerMenu(this);
    mp_menu->show();
    this->hide();
}
