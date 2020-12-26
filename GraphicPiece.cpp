#include "GraphicPiece.h"
#include "QPainter"
#include "QStyleOptionGraphicsItem"
#include "QtGui"
#include <string>
#include <iostream>
#include <QDir>


GraphicPiece::GraphicPiece(FIELDSTATE player, QGraphicsItem * parent): QGraphicsItem(parent), m_player(player) {}

GraphicPiece::GraphicPiece(QGraphicsItem * parent): QGraphicsItem(parent), m_player(FIELDSTATE::EMPTY) {}

QRectF GraphicPiece::boundingRect() const {
    return QRectF(0, 0, 30, 30);
}

void GraphicPiece::paint(QPainter * painter,
    const QStyleOptionGraphicsItem * option, QWidget * widget) {
    Q_UNUSED(option)
    Q_UNUSED(widget)

    QImage image = QImage(QString("../02-the-mill-game/images/circle.jpg"));
    painter -> drawImage(QRectF(0, 0, 30, 30), image);

    if (m_player == FIELDSTATE::PLAYER_1)
        painter -> drawImage(QRectF(-1, -1, 32, 32), QImage(QString("../02-the-mill-game/images/blue_circle.png")));
    else if (m_player == FIELDSTATE::PLAYER_2)
        painter -> drawImage(QRectF(-1, -1, 32, 32), QImage(QString("../02-the-mill-game/images/red_circle.png")));
}

void GraphicPiece::set_player(FIELDSTATE p) {
    m_player = p;
}
