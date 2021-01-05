#include "code/include/MyGraphicsScene.h"
#include <iostream>
#include <QGraphicsSceneMouseEvent>
#include <QDebug>
#include "code/include/Lib.h"

void MyGraphicsScene::mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent) {

    QGraphicsScene::mousePressEvent(mouseEvent);

    if (mouseEvent->isAccepted()) {
        return;
    } else {
        emit signalClickedSomething(mouseEvent->scenePos());
    }
}

MyGraphicsScene::MyGraphicsScene() {
    setRedPieces(NUM_OF_PIECES);
    setBluePieces(NUM_OF_PIECES);
}

int MyGraphicsScene::getRedPieces() {
    return this->redPieces;
}

int MyGraphicsScene::getBluePieces() {
    return this->bluePieces;
}

void MyGraphicsScene::setRedPieces(int value) {
    this->redPieces = value;
}

void MyGraphicsScene::setBluePieces(int value) {
    this->bluePieces = value;
}

void MyGraphicsScene::decrementRedPieces() {
    this->redPieces--;
}

void MyGraphicsScene::decrementBluePieces() {
    this->bluePieces--;
}
