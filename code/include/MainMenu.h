#ifndef MAINMENU_H
#define MAINMENU_H

#include <QMainWindow>
#include "Board.h"
#include "MultiplayerMenu.h"
#include "LocalGameMenu.h"

namespace Ui {
    class MainMenu;
}

class MainMenu : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainMenu(QWidget *parent = 0);
    ~MainMenu();

private slots:
    void on_localPlayBtn_clicked();
    void on_serverPlayBtn_clicked();
    void on_aiPlayBtn_clicked();

public slots:
    void on_btnBackMainClicked();

private:
    Ui::MainMenu    *ui;
    MultiplayerMenu *mp_menu =nullptr;
    LocalGameMenu   *lg_menu = nullptr;
};
#endif // MAINMENU_H
