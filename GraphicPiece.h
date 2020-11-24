#ifndef GRAPHIC_PIECE_H
#define GRAPHIC_PIECE_H

#include "QGraphicsItem"
#include "lib.h"

/*
Klasa za crtanje figurice, nasledjuje QGraphicsItem i ove dve cisto virtuelne metode boundingRect i paint.
*/

class GraphicPiece : public QGraphicsItem {
    public:
        GraphicPiece(FIELDSTATE player, QGraphicsItem* parent = nullptr);
        GraphicPiece(QGraphicsItem* parent = nullptr);

        QRectF boundingRect () const override;

        void paint(QPainter *painter , const QStyleOptionGraphicsItem *option , QWidget *widget) override;

        void set_player(FIELDSTATE p);

    private:
        FIELDSTATE m_player;
};

#endif // GRAPHIC_PIECE_H
