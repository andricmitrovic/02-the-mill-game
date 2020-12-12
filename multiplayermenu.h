#ifndef MULTIPLAYERMENU_H
#define MULTIPLAYERMENU_H

#include <QMainWindow>

namespace Ui {
class MultiplayerMenu;
}

class MultiplayerMenu : public QMainWindow
{
    Q_OBJECT

public:
    explicit MultiplayerMenu(QWidget *parent = nullptr);
    ~MultiplayerMenu();

private:
    Ui::MultiplayerMenu *ui;
};

#endif // MULTIPLAYERMENU_H
