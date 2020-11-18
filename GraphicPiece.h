#ifndef GRAPHIC_PIECE_H
#define GRAPHIC_PIECE_H

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

class GraphicPiece : public QGraphicsItem {
    public:
        GraphicPiece(VALUE player, QGraphicsItem* parent = nullptr);
        GraphicPiece(QGraphicsItem* parent = nullptr);

        QRectF boundingRect () const override;

        void paint(QPainter *painter , const QStyleOptionGraphicsItem *option , QWidget *widget) override;

        void set_player(VALUE p);

    private:
        VALUE m_player;
};

#endif // GRAPHIC_PIECE_H
