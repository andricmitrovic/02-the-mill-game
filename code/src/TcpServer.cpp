#include "code/include/TcpServer.h"
#include "code/include/Lib.h"

#include <QtNetwork>
#include <QJsonDocument>
#include <QJsonValue>
#include <QPlainTextEdit>

TcpServer::TcpServer(QWidget *parent) :
        m_server(new QTcpServer(this)) {

    m_server->listen(QHostAddress::LocalHost, 12345);
    connect(m_server, SIGNAL(newConnection()), this, SLOT(newConnection()));
}

TcpServer::~TcpServer() {
    delete m_server;
    for (auto client : m_clients)
        delete client;
}

void TcpServer::newConnection() {
    while (m_server->hasPendingConnections() && m_clients.size() < 2) {
        QTcpSocket *con = m_server->nextPendingConnection();

        m_clients << con;

        connect(con, SIGNAL(disconnected()), this, SLOT(removeConnection()));
        connect(con, SIGNAL(readyRead()), this, SLOT(newMessage()));

        if (m_clients.size() == 2) {
            for (int i = 0; i < m_clients.size(); i++) {
                QJsonObject message;
                message.insert("game_move", static_cast<int>(GAMEMOVE::INIT));
                message.insert("game_start", QJsonValue(true));
                message.insert("player_id", QJsonValue(i));
                message.insert("turn", QJsonValue(!i).toBool());

                QJsonDocument doc = QJsonDocument(message);
                m_clients[i]->write(doc.toJson());

            }
        }
    }
}

void TcpServer::removeConnection() {
    if (QTcpSocket * con = qobject_cast<QTcpSocket *>(sender())) {
        m_clients.removeOne(con);
        con->deleteLater();
    }
}

void TcpServer::newMessage() {
    if (QTcpSocket * con = qobject_cast<QTcpSocket *>(sender())) {
        m_receivedData[con].clear();
        m_receivedData[con].append(con->readAll());

        QByteArray messages = m_receivedData[con];

        foreach(QTcpSocket * socket, m_clients)
        {
            if (socket == con)
                continue;
            if (socket->state() == QAbstractSocket::ConnectedState)
                socket->write(messages);
        }
    }
}
