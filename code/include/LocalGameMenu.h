#ifndef LOCALGAMEMENU_H
#define LOCALGAMEMENU_H

#include <QMainWindow>
#include "Board.h"

namespace Ui {
class LocalGameMenu;
}

class LocalGameMenu : public QMainWindow
{
    Q_OBJECT

public:
    explicit LocalGameMenu(QWidget *parent = nullptr);
    ~LocalGameMenu();

private slots:
    void on_btnStartGame_clicked();

private:
    Ui::LocalGameMenu *ui;
    Board *board;
};

#endif // LOCALGAMEMENU_H
