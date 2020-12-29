#include "code/include/TcpClient.h"

#include <QtNetwork>
#include <QDebug>
#include <iostream>

TcpClient::TcpClient(FIELDSTATE playerId, QString playerName)
    : Player(playerId, playerName), m_socket(new QTcpSocket()), m_gameStart(false), m_millOccured(false){


    connect(m_socket, SIGNAL(readyRead()), this, SLOT(readMessage()), Qt::DirectConnection);
    //connect(this, SIGNAL(readFinished()), this, SLOT(onReadFinished()));

    this->setToIndex(-1);
    this->setFromIndex(-1);

    if (this->id() != FIELDSTATE::EMPTY && this->getSocket()->state() != QAbstractSocket::ConnectedState) {
        this->getSocket()->connectToHost(QHostAddress::LocalHost, 12345);
    }
}

void TcpClient::readMessage() {

    QString serverMessage = (QString)(this->m_socket->readAll());
    QJsonDocument readDocument = QJsonDocument::fromJson(serverMessage.toUtf8());

    if (readDocument.isEmpty()){
        return;
    }


    QJsonObject jObj = readDocument.object();

    setMove( GAMEMOVE (jObj.value(QString("game_move")).toInt()));


    if (move == GAMEMOVE :: INIT){

        this->m_gameStart = jObj.value(QString("game_start")).toBool();

        this->setTurn(jObj.value(QString("turn")).toBool());

        FIELDSTATE player_id = jObj.value(QString("player_id")).toInt() == 0? FIELDSTATE::PLAYER_1 : FIELDSTATE :: PLAYER_2;

        this->setId(player_id);


        emit over(move);
     }
    else if (move == GAMEMOVE :: PLACE){

        this->setToIndex(jObj.value(QString("toIndex")).toInt());
        this->m_millOccured = jObj.value(QString("mill_occured")).toBool();


        emit over(move);

    }else if (move == GAMEMOVE :: REMOVE){
        this->setFromIndex(jObj.value(QString("FromIndex")).toInt());
        this->m_millOccured = false;
        emit over(move);
    }else if (move == GAMEMOVE :: MOVE) {
        this->setToIndex(jObj.value(QString("toIndex")).toInt());
        this->m_millOccured = jObj.value(QString("mill_occured")).toBool();
        this->setFromIndex(jObj.value(QString("FromIndex")).toInt());

        emit over(move);
    }else{
        this->setFromIndex(jObj.value(QString("FromIndex")).toInt());
        emit over(move);
    }

}

void TcpClient::onReadFinished() {

}

void TcpClient::setMove(GAMEMOVE value) {
    move = value;
}

void TcpClient::setToIndex(int value) {
    toIndex = value;
}

void TcpClient::setFromIndex(int value) {
    fromIndex = value;
}

GAMEMOVE TcpClient::getMove() const {
    return move;
}

int TcpClient::getToIndex() const {
    return toIndex;
}

int TcpClient::getFromIndex() const {
    return fromIndex;
}


QTcpSocket *TcpClient::getSocket() const {
    return m_socket;
}

