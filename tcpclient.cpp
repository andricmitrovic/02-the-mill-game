#include "tcpclient.h"

#include <QtNetwork>
#include <QDebug>

TcpClient::TcpClient(FIELDSTATE playerId, QString playerName)
    : Player(playerId, playerName), m_socket(new QTcpSocket()) {


    connect(m_socket, SIGNAL(readyRead()), this, SLOT(readMessage()));
    connect(this, SIGNAL(readFinished()), this, SLOT(onReadFinished()), Qt::DirectConnection);

    this->setToIndex(-1);
    this->setFromIndex(-1);

    if (this->id() != FIELDSTATE::EMPTY && this->getSocket()->state() != QAbstractSocket::ConnectedState) {
        this->getSocket()->connectToHost(QHostAddress::LocalHost, 12345);
    }
}

void TcpClient::readMessage() {
    this->m_receivedData.clear();
    if (m_socket->state() != QAbstractSocket::ConnectedState) {
        m_receivedData.append(QString("Not connected"));
        return;
    }
    m_receivedData.append(QString(m_socket->readAll()));

    if (!m_receivedData.contains(QChar(23))) {
        m_receivedData.append(QString("Not whole"));
        //emit readFinished();
        return;
    } else {
        emit readFinished();
        return;
    }
}

void TcpClient::onReadFinished() {

   // qDebug() << m_receivedData;

    QStringList data = m_receivedData.split(" ");
    GAMEMOVE move = (GAMEMOVE)(data[1].toInt());
    setMove(move);

    if (move == GAMEMOVE::INIT){
        emit over(move);
    }
    else if (move == GAMEMOVE::PLACE) {

        int index = data[2].toInt();

        this->setToIndex(index);

        this->changeTurn();
        emit over(move);
    }
    else if (move == GAMEMOVE::MOVE) {
        int index1 = data[2].toInt();
        int index2 = data[3].toInt();
        this->setFromIndex(index1);
        this->setToIndex(index2);
        this->changeTurn();
    }
    else{
        int index = data[2].toInt();
        this->setFromIndex(index);
    }


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

QString TcpClient::getReceivedData() const {
    return m_receivedData;
}
