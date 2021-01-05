#include "code/include/Piece.h"
#include "QPainter"
#include "QStyleOptionGraphicsItem"
#include "QtGui"

Piece::Piece(FIELDSTATE player, QGraphicsItem *parent) : QGraphicsItem(parent), m_player(player) {}

QRectF Piece::boundingRect() const {
    return QRectF(0, 0, 30, 30);
}

void Piece::paint(QPainter *painter,
                  const QStyleOptionGraphicsItem *option, QWidget *widget) {
    Q_UNUSED(option)
    Q_UNUSED(widget)

    if (m_player == FIELDSTATE::PLAYER_1)
        painter->drawImage(QRectF(-1, -1, 32, 32),
                           QImage(QString("../02-the-mill-game/code/resources/images/blue_circle.png")));
    else if (m_player == FIELDSTATE::PLAYER_2)
        painter->drawImage(QRectF(-1, -1, 32, 32),
                           QImage(QString("../02-the-mill-game/code/resources/images/red_circle.png")));
}
