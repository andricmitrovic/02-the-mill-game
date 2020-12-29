#include "code/include/TcpServer.h"
#include <ui_tcpserver.h>

#include "code/include/Lib.h"

#include <QtNetwork>
#include <QJsonDocument>
#include <QJsonValue>
#include <QPlainTextEdit>

TcpServer::TcpServer(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TcpServer)
  , m_server(new QTcpServer(this))
{
    ui->setupUi(this);

    if (!m_server->listen(QHostAddress::LocalHost, 12345)) {
        ui->log->setPlainText("Failure while starting server: "+ m_server->errorString());
        return;
    }
    connect(m_server, SIGNAL(newConnection()), this, SLOT(newConnection()));
}

TcpServer::~TcpServer()
{
    delete ui;
}

void TcpServer::newConnection()
{
    while (m_server->hasPendingConnections() && m_clients.size() < 2) {

        QTcpSocket *con = m_server->nextPendingConnection();

        m_clients << con;

        connect(con, SIGNAL(disconnected()), this, SLOT(removeConnection()));
        connect(con, SIGNAL(readyRead()), this, SLOT(newMessage()));

        ui->log->insertPlainText(QString("* New connection: %1, port %2 %3\n")

                                 .arg(con->peerAddress().toString())
                                 .arg(QString::number(con->peerPort()))
                                 .arg(con->openMode()));


        if (m_clients.size() == 2){
            for (int i=0; i<m_clients.size(); i++){

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

void TcpServer::removeConnection()
{
    if (QTcpSocket *con = qobject_cast<QTcpSocket*>(sender())) {
        ui->log->insertPlainText(QString("* Connection removed: %1, port %2\n")
                                 .arg(con->peerAddress().toString())
                                 .arg(QString::number(con->peerPort())));
        m_clients.removeOne(con);
        con->deleteLater();
    }
}

void TcpServer::newMessage()
{
    if (QTcpSocket *con = qobject_cast<QTcpSocket*>(sender())) {
        m_receivedData[con].clear();
        m_receivedData[con].append(con->readAll());


        QByteArray messages = m_receivedData[con];

        ui->log->insertPlainText("Sending message: \n");
        foreach (QTcpSocket *socket, m_clients) {
            if (socket == con)
                continue;
            if (socket->state() == QAbstractSocket::ConnectedState){

                socket->write(messages);
             }
        }
    }
}
