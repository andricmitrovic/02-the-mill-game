#ifndef BOARD_H
#define BOARD_H

#include <QMainWindow>
#include <QLabel>
#include <QWidget>
#include <QPushButton>
#include <QGridLayout>
#include <QSignalMapper>
#include <QGraphicsScene>
#include <QGraphicsTextItem>
#include <QHBoxLayout>
#include <QPixmap>

#include <vector>
#include "gamemap.h"
#include "game.h"


QT_BEGIN_NAMESPACE
namespace Ui { class Board; }
QT_END_NAMESPACE

class Board : public QMainWindow
{
    Q_OBJECT


public:
    Board(QWidget *parent = nullptr);
    ~Board();

// slotovi za registrovanje selekcija odnosno klika na kvadrate
public slots:
    void onFieldSelection();

private:
    Ui::Board       *ui;
    //GameMap         *gm;
    Game            *g;
    QGraphicsScene  m_scene;
};
#endif // BOARD_H
