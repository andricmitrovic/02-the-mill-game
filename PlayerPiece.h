#ifndef PLAYER_PIECE_H
#define PLAYER_PIECE_H

#include "QGraphicsItem"

enum class VALUE
{
    EMPTY,
    PLAYER_1,
    PLAYER_2
};

/*
Klasa za crtanje figurice, nasledjuje QGraphicsItem i ove dve cisto virtuelne metode boundingRect i paint.
*/

class PlayerPiece : public QGraphicsItem {
    public:
        PlayerPiece(VALUE player, QGraphicsItem* parent = nullptr);

        QRectF boundingRect () const override;

        void paint(QPainter *painter , const QStyleOptionGraphicsItem *option , QWidget *widget) override;

    private:
        VALUE m_player;
};

#endif // PLAYER_PIECE_H
