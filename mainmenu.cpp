#include "mainmenu.h"
#include "ui_mainmenu.h"
#include "board.h"

MainMenu::MainMenu(QWidget *parent, Board *board) :
    QMainWindow(parent),
    ui(new Ui::MainMenu)
{
    ui->setupUi(this);
    this->board = board;
}

MainMenu::~MainMenu()
{
    delete ui;
}

void MainMenu::on_localPlayBtn_clicked()
{
    this->hide();
    this->board->show();
}
