#ifndef GRAPHICLINE_H
#define GRAPHICLINE_H

#include "QGraphicsItem"
#include "Lib.h"

/*
 * Class for drawing lines on the board
 */
class GraphicLine : public QGraphicsItem {

public:
    QRectF boundingRect() const override;

    GraphicLine(QGraphicsItem *parent = nullptr, float width = 3, float height = 3);

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

    float getWidth() const;
    float getHeight() const;

private:
    float width;
    float height;
};
#endif // GRAPHICLINE_H
