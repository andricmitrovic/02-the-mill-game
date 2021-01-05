#ifndef GRAPHIC_PIECE_H
#define GRAPHIC_PIECE_H

#include <QCoreApplication>
#include "QGraphicsItem"
#include "Lib.h"

/*
 * Class for drawing fields and pieces on the board
 */
class GraphicPiece : public QGraphicsItem {

public:
    void set_player(FIELDSTATE p);

    QRectF boundingRect() const override;

    GraphicPiece(QGraphicsItem *parent = nullptr);

    GraphicPiece(FIELDSTATE player, QGraphicsItem *parent = nullptr);

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

private:
    FIELDSTATE m_player;
};
#endif // GRAPHIC_PIECE_H
