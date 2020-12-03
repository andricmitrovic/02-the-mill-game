#ifndef GRAPHIC_PIECE_H
#define GRAPHIC_PIECE_H

#include <QCoreApplication>
#include "QGraphicsItem"
#include "lib.h"

/*
Klasa za crtanje figurice, nasledjuje QGraphicsItem i ove dve cisto virtuelne metode boundingRect i paint.
*/

class GraphicPiece : public QGraphicsItem {
    public:

        void set_player(FIELDSTATE p);

        QRectF boundingRect () const override;

        GraphicPiece(QGraphicsItem* parent = nullptr);

        GraphicPiece(FIELDSTATE player, QGraphicsItem* parent = nullptr);

        void paint(QPainter *painter , const QStyleOptionGraphicsItem *option , QWidget *widget) override;


    private:
        FIELDSTATE m_player;
};

#endif // GRAPHIC_PIECE_H
