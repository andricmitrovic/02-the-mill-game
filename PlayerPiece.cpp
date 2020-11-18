#include "PlayerPiece.h"

#include "QPainter"
#include "QStyleOptionGraphicsItem"

PlayerPiece::PlayerPiece(QGraphicsItem* parent) : QGraphicsItem(parent)
{}

QRectF PlayerPiece::boundingRect() const
{
    return QRectF(0, 0, 10, 10);
}

void PlayerPiece::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option)
    Q_UNUSED(widget)
    painter->fillRect(boundingRect(), Qt::black);
}
