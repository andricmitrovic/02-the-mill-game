#ifndef PIECE_H
#define PIECE_H

#include "QGraphicsItem"
#include "Lib.h"

class Piece : public QGraphicsItem {

public:
    void set_player(FIELDSTATE p);

    QRectF boundingRect() const override;

    Piece(FIELDSTATE player, QGraphicsItem *parent = nullptr);

    void paint(QPainter *painter,
               const QStyleOptionGraphicsItem *option, QWidget *widget) override;

private:
    FIELDSTATE m_player;
};
#endif // PIECE_H
