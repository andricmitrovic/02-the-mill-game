#include "code/include/MainMenu.h"
#include <ui_mainmenu.h>

MainMenu::MainMenu(QWidget *parent) :
        QMainWindow(parent),
        ui(new Ui::MainMenu) {
    ui->setupUi(this);
}

MainMenu::~MainMenu() {
    delete ui;
    delete mp_menu;
    delete lg_menu;
}

void MainMenu::on_localPlayBtn_clicked() {
    lg_menu = new LocalGameMenu(this);
    connect(lg_menu, SIGNAL(back()), this, SLOT(on_btnBackMainClicked()));
    lg_menu->show();
    this->hide();
}

void MainMenu::on_aiPlayBtn_clicked() {
    mp_menu = new MultiplayerMenu(this);
    connect(mp_menu, SIGNAL(back()), this, SLOT(on_btnBackMainClicked()));
    mp_menu->show();
    this->hide();
}

void MainMenu::on_serverPlayBtn_clicked() {
    mp_menu = new MultiplayerMenu(this, GAMEMODE::SERVER);
    connect(mp_menu, SIGNAL(back()), this, SLOT(on_btnBackMainClicked()));
    mp_menu->show();
    this->hide();
}

void MainMenu::on_btnBackMainClicked() {
    if (mp_menu != nullptr)
        mp_menu->close();
    else
        lg_menu->close();

    this->show();
}
