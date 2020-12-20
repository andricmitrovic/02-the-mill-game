#include "tcpserver.h"
#include "ui_tcpserver.h"
#include "lib.h"

#include <QtNetwork>
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
    while (m_server->hasPendingConnections()) {
        QTcpSocket *con = m_server->nextPendingConnection();

        m_clients << con;

        connect(con, SIGNAL(disconnected()), this, SLOT(removeConnection()));
        connect(con, SIGNAL(readyRead()), this, SLOT(newMessage()));

        ui->log->insertPlainText(QString("* New connection: %1, port %2 %3\n")

                                 .arg(con->peerAddress().toString())
                                 .arg(QString::number(con->peerPort()))
                                 .arg(con->openMode()));

        if (m_clients.size() == 2){
            GAMEMOVE move = GAMEMOVE::INIT;
            QString message = QString::number(2) + QString(" ") + QString::number((int) (move)) + QString(" ") + QChar(23);
            m_clients[1]->write(message.toLocal8Bit());
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
        m_receivedData[con].append(con->readAll());
        if (!m_receivedData[con].contains(QChar(23)))
            return;

        QStringList messages = m_receivedData[con].split(QChar(23));
        m_receivedData[con] = messages.takeLast();
        foreach (QString message, messages) {
            ui->log->insertPlainText("Sending message: " + message + "\n");
            message.append(QChar(23));
            foreach (QTcpSocket *socket, m_clients) {
                if (socket == con)
                    continue;
                if (socket->state() == QAbstractSocket::ConnectedState){
                    socket->write(message.toLocal8Bit());
                    ui->log->insertPlainText("Message sent \n" + message.toLocal8Bit());

                }
                else
                    ui->log->insertPlainText("Not conneted \n");
            }

        }
    }
}
