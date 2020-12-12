#ifndef MAINMENU_H
#define MAINMENU_H

#include <QMainWindow>
#include "board.h"

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

private:
    Ui::MainMenu *ui;
    Board *board;
};

#endif // MAINMENU_H
