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
#include "MyGraphicsScene.h"


QT_BEGIN_NAMESPACE
namespace Ui { class Board; }
QT_END_NAMESPACE

class Board : public QMainWindow {
    Q_OBJECT

public:
    Board(QWidget *parent = nullptr);
    ~Board();
    Game* getGame();
    void resizeEvent(QResizeEvent* event);

// slotovi za registrovanje selekcija odnosno klika na kvadrate
public slots:
    void onFieldSelection(QPointF);
    void writeGameMessage();

private:
    Ui::Board       *ui;
    Game            *game;
    MyGraphicsScene  m_scene;
};
#endif // BOARD_H
