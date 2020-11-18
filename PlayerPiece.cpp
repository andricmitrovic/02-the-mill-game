#include "PlayerPiece.h"

#include "QPainter"
#include "QStyleOptionGraphicsItem"
#include "QtGui"

PlayerPiece::PlayerPiece(QGraphicsItem* parent) : QGraphicsItem(parent), m_color(true)
{}

QRectF PlayerPiece::boundingRect() const
{
    return QRectF(0, 0, 10, 10);
}

void PlayerPiece::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option)
    Q_UNUSED(widget)

    if(m_color)
        painter->fillRect(boundingRect(), Qt::black);
    else
        painter->fillRect(boundingRect(), Qt::white);
}
