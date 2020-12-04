#include "MyGraphicsScene.h"
#include <iostream>
#include <QGraphicsSceneMouseEvent>
#include <QDebug>

void MyGraphicsScene::mousePressEvent ( QGraphicsSceneMouseEvent * mouseEvent )
{

    QGraphicsScene::mousePressEvent ( mouseEvent );

    if( mouseEvent->isAccepted() )
    {
        return;
    }
    else
    {
        emit signalClickedSomething(mouseEvent->scenePos());

        //qDebug() << mouseEvent->scenePos();
        //qDebug() << this->width();
        //qDebug() << this->height();

        //update();
        //QGraphicsScene::mousePressEvent(mouseEvent);
    }


 //if the event has not been processed by an item create a new item here
}
