#ifndef PLAYER_PIECE_H
#define PLAYER_PIECE_H

#include "QGraphicsItem"

/*
Klasa za crtanje figurice, nasledjuje QGraphicsItem i ove dve cisto virtuelne metode boundingRect i paint.
*/

class PlayerPiece : public QGraphicsItem {
    public:
        PlayerPiece(QGraphicsItem* parent = nullptr);

        QRectF boundingRect () const override;

        void paint(QPainter *painter , const QStyleOptionGraphicsItem *option , QWidget *widget) override;

    private:
        bool m_color;
};

#endif // PLAYER_PIECE_H
