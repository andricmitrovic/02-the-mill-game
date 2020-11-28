#include "GraphicPiece.h"
#include "QPainter"
#include "QStyleOptionGraphicsItem"
#include "QtGui"

GraphicPiece::GraphicPiece(FIELDSTATE player, QGraphicsItem * parent): QGraphicsItem(parent), m_player(player) {}

GraphicPiece::GraphicPiece(QGraphicsItem * parent): QGraphicsItem(parent), m_player(FIELDSTATE::EMPTY) {}

QRectF GraphicPiece::boundingRect() const {
    return QRectF(0, 0, 30, 30);
}

void GraphicPiece::paint(QPainter * painter,
    const QStyleOptionGraphicsItem * option, QWidget * widget) {
    Q_UNUSED(option)
    Q_UNUSED(widget)

    if (m_player == FIELDSTATE::EMPTY)
        painter -> fillRect(boundingRect(), Qt::black);
    else if (m_player == FIELDSTATE::PLAYER_1)
        painter -> fillRect(boundingRect(), Qt::white);
    else if (m_player == FIELDSTATE::PLAYER_2)
        painter -> fillRect(boundingRect(), Qt::blue);
}

void GraphicPiece::set_player(FIELDSTATE p) {
    m_player = p;
}
