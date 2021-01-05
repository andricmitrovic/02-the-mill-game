#ifndef BOARD_H
#define BOARD_H

#include <QLabel>
#include <QWidget>
#include <QHBoxLayout>
#include <QMainWindow>
#include <QPushButton>
#include <QGridLayout>
#include <QSignalMapper>
#include <QGraphicsScene>
#include <QGraphicsTextItem>

#include <vector>

#include "Game.h"
#include "GameAi.h"
#include "GameServer.h"

#include "GameMap.h"

#include "MyGraphicsScene.h"
#include "Help.h"


QT_BEGIN_NAMESPACE
namespace Ui { class Board; }
QT_END_NAMESPACE

class Board : public QMainWindow {
    Q_OBJECT

public:
    Board(QWidget *parent = nullptr, GAMEMODE gameMode=GAMEMODE::LOCAL, QString player1_name="", QString player2_name="");
    ~Board();
    Game* getGame();
    void resizeEvent(QResizeEvent* event);

signals:
    void sendServerMessage(QString message);

// slotovi za registrovanje selekcija odnosno klika na kvadrate
public slots:
    void onFieldSelection(QPointF);
    void writeGameMessage();
    void writeErrorMessage();
    void writeServerMessage(QString message);
    void up_scene();
    void on_btnHelp_clicked();
    void on_btnBack_clicked();

private:
    Ui::Board         *ui;
    Game              *game;
    MyGraphicsScene   *m_scene;
    Help              *help;
    GAMEMODE          game_mode;

signals:
    void clickedBack();

};
#endif // BOARD_H
