#include "code/include/MainMenu.h"
#include <ui_mainmenu.h>

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
    lg_menu = new LocalGameMenu(this);
    lg_menu->show();
    this->hide();
}

void MainMenu::on_aiPlayBtn_clicked()
{
    mp_menu = new MultiplayerMenu(this);
    mp_menu->show();
    this->hide();
}

void MainMenu::on_serverPlayBtn_clicked()
{
    mp_menu = new MultiplayerMenu(this, GAMEMODE::SERVER);
    mp_menu->show();
    this->hide();
}
