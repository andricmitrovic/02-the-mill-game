#ifndef PLAYER_PIECE_H
#define PLAYER_PIECE_H

#include "QGraphicsItem"

class PlayerPiece : public QGraphicsItem {
    public:
        PlayerPiece(QGraphicsItem* parent = nullptr);

        QRectF boundingRect () const override;

        void paint(QPainter *painter , const QStyleOptionGraphicsItem *option , QWidget *widget) override;

};

#endif // PLAYER_PIECE_H
