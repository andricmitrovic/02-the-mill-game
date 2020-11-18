#include "PlayerPiece.h"

#include "QPainter"
#include "QStyleOptionGraphicsItem"
#include "QtGui"

PlayerPiece::PlayerPiece(VALUE player, QGraphicsItem* parent) : QGraphicsItem(parent), m_player(player)
{}

QRectF PlayerPiece::boundingRect() const
{
    return QRectF(0, 0, 30, 30);
}

void PlayerPiece::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option)
    Q_UNUSED(widget)

    if(m_player == VALUE::EMPTY)
        painter->fillRect(boundingRect(), Qt::black);
    else if(m_player == VALUE::PLAYER_1)
        painter->fillRect(boundingRect(), Qt::white);
    else if(m_player == VALUE::PLAYER_2)
        painter->fillRect(boundingRect(), Qt::blue);
}
