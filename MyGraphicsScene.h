#ifndef MYGRAPHICSVIEW_H
#define MYGRAPHICSVIEW_H

#include "QGraphicsScene"

class MyGraphicsScene : public QGraphicsScene {
    Q_OBJECT

signals:
    void signalClickedSomething(QPointF);

protected:
    virtual void mousePressEvent(QGraphicsSceneMouseEvent * mouseEvent);
};

#endif // MYGRAPHICSVIEW_H
