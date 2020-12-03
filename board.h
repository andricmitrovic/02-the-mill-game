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
#include "game.h"
#include "gamemap.h"


QT_BEGIN_NAMESPACE
namespace Ui { class Board; }
QT_END_NAMESPACE

class Board : public QMainWindow {
    Q_OBJECT

public:
    Board(QWidget *parent = nullptr);
    ~Board();

    Game* getGame();

// slotovi za registrovanje selekcija odnosno klika na kvadrate

public slots:
    void onFieldSelection();
    void writeGameMessage();

private:
    Ui::Board       *ui;

    Game            *game;
    QGraphicsScene  m_scene;
};
#endif // BOARD_H
