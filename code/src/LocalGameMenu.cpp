#include "code/include/LocalGameMenu.h"
#include "ui_localgamemenu.h"

LocalGameMenu::LocalGameMenu(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::LocalGameMenu)
{
    ui->setupUi(this);


}

LocalGameMenu::~LocalGameMenu()
{
    delete ui;
}

void LocalGameMenu::on_btnStartGame_clicked()
{
    this->hide();
    board = new Board(this, GAMEMODE::LOCAL, ui->lePlayer1Name->text(), ui->lePlayer2Name->text());
    connect(board, &Board ::clickedBack, this, & LocalGameMenu:: on_btnBackLocalClicked);
    board->show();
}

void LocalGameMenu::on_btnBackLocalClicked()
{
    board->close();

    emit back();
}
