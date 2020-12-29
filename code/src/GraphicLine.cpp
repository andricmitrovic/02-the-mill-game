#include "code/include/GraphicLine.h"
#include <QPainter>
#include <QStyleOptionGraphicsItem>
#include <QtGui>


GraphicLine::GraphicLine(QGraphicsItem * parent, float width, float height): QGraphicsItem(parent), width(width), height(height){}

QRectF GraphicLine::boundingRect() const {
    return QRectF(0, 0, width, height);
}

void GraphicLine::paint(QPainter * painter,
    const QStyleOptionGraphicsItem * option, QWidget * widget) {
    Q_UNUSED(option)
    Q_UNUSED(widget)
    painter -> fillRect(boundingRect(), Qt::black);
}

float GraphicLine::getWidth() const{
    return width;
}

float GraphicLine::getHeight() const{
    return height;
}
