#include "tcpclient.h"

#include <QtNetwork>
#include <QDebug>

TcpClient::TcpClient(FIELDSTATE playerId, QString playerName)
    : Player(playerId, playerName), m_socket(new QTcpSocket()) {


    connect(m_socket, SIGNAL(readyRead()), this, SLOT(readMessage()));
    connect(this, SIGNAL(readFinished()), this, SLOT(onReadFinished()), Qt::DirectConnection);

    if (this->id() != FIELDSTATE::EMPTY && this->getSocket()->state() != QAbstractSocket::ConnectedState) {
        this->getSocket()->connectToHost(QHostAddress::LocalHost, 12345);
    }
}

void TcpClient::readMessage() {

    if (m_socket->state() != QAbstractSocket::ConnectedState) {
        m_receivedData.append(QString("Not connected"));
        return;
    }
    m_receivedData.append(QString(m_socket->readAll()));

    if (!m_receivedData.contains(QChar(23))) {
        m_receivedData.append(QString("Not whole"));
        emit readFinished();
        return;
    } else {
        emit readFinished();
        return;
    }
}

void TcpClient::onReadFinished() {
    qDebug() << m_receivedData;

    QStringList data = m_receivedData.split(" ");
    GAMEMOVE move = (GAMEMOVE)(data[1].toInt());
    setMove(move);

    if (move == GAMEMOVE::INIT){
        int index = data[0].toInt();
        if (index == 1){
            this->setId(FIELDSTATE::PLAYER_1);
            this->setTurn(true);
        }else{
            this->setId(FIELDSTATE::PLAYER_2);
            this->setTurn(false);
        }
    }
    if (move == GAMEMOVE::PLACE) {
        int index = data[2].toInt();
        this->setToIndex(index);
    }
    if (move == GAMEMOVE::MOVE) {
        int index1 = data[2].toInt();
        int index2 = data[3].toInt();
        this->setFromIndex(index1);
        this->setToIndex(index2);
    }
    if (move == GAMEMOVE::REMOVE) {
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
