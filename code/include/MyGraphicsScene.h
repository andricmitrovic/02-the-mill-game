#ifndef MYGRAPHICSVIEW_H
#define MYGRAPHICSVIEW_H

#include "QGraphicsScene"
#include <QPushButton>

class MyGraphicsScene : public QGraphicsScene {
    Q_OBJECT

signals:
    void signalClickedSomething(QPointF);

protected:
    virtual void mousePressEvent(QGraphicsSceneMouseEvent * mouseEvent);

public:
    MyGraphicsScene();

    int getRedPieces();
    int getBluePieces();
    void setRedPieces(int value);
    void setBluePieces(int value);

    void decrementRedPieces();
    void decrementBluePieces();

private:
    int redPieces;
    int bluePieces;
};
#endif // MYGRAPHICSVIEW_H
