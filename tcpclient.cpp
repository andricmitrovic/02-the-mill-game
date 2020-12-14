#include "tcpclient.h"

#include <QtWidgets>
#include <QtNetwork>
#include <QDebug>

TcpClient::TcpClient(FIELDSTATE playerId, QString playerName) :
  m_socket(new QTcpSocket()),
  m_player(Player(playerId, playerName))
{
//    ui->setupUi(this);
//    ui->address->setText(QHostAddress(QHostAddress::LocalHost).toString());
//    ui->port->setValue(52693);

//    ui->text->setFocus();


    connect(m_socket, SIGNAL(readyRead()), this, SLOT(readMessage()));
    connect(m_socket, SIGNAL(connected()), this, SLOT(connectedToServer()));
    connect(m_socket, SIGNAL(disconnected()), this, SLOT(disconnectByServer()));
    connect(this, SIGNAL(readFinished()), this, SLOT(onReadFinished()), Qt::DirectConnection);
}


TcpClient::~TcpClient()
{
}

//void TcpClient::on_text_returnPressed()
//{
//    const QString text = ui->text->text().simplified();
//    if (text.isEmpty()
//            || m_socket->state() != QAbstractSocket::ConnectedState)
//        return;

//    QString message = m_user + ": " + ui->text->text() + QChar(23);
//    m_socket->write(message.toLocal8Bit());
//    ui->text->clear();
//}

void TcpClient::readMessage()
{
    if (m_socket->state() != QAbstractSocket::ConnectedState){
        m_receivedData.append(QString("Not connected"));
        return;
    }
    m_receivedData.append(QString(m_socket->readAll()));

    if (!m_receivedData.contains(QChar(23))){
        m_receivedData.append(QString("Not whole"));
        emit readFinished();
        return;
    }else{
        emit readFinished();
        return;
    }
}

//void TcpClient::on_connect_clicked()
//{
//    const QString user = ui->user->text().simplified();
//    if (user.isEmpty()) {
//        ui->chat->insertPlainText("== Unable to connect to server. You must define an user name.\n");
//        return;
//    }

//    m_user = user;

//    if (m_socket->state() != QAbstractSocket::ConnectedState) {
//        ui->chat->insertPlainText("== Connecting...\n");
//        m_socket->connectToHost(ui->address->text(), ui->port->value());
//        updateGui(QAbstractSocket::ConnectingState);
//    }
//}

void TcpClient::connectedToServer()
{
    //ui->chat->insertPlainText("== Connected to server.\n");
    updateGui(QAbstractSocket::ConnectedState);
    this->getReceivedData().append(QString("Connected") + getPlayer().getName());
}

//void TcpClient::on_disconnect_clicked()
//{
//    if (m_socket->state() != QAbstractSocket::ConnectingState) {
//        ui->chat->insertPlainText("== Abort connecting.\n");
//    }
//    m_socket->abort();
//    updateGui(QAbstractSocket::UnconnectedState);
//}

void TcpClient::disconnectByServer()
{
    //ui->chat->insertPlainText("== Disconnected by server.\n");
    updateGui(QAbstractSocket::UnconnectedState);
}

void TcpClient::onReadFinished()
{
    qDebug() << m_receivedData;
}

Player TcpClient::getPlayer()
{
    return m_player;
}

QTcpSocket *TcpClient::getSocket(){
    return m_socket;
}

QString TcpClient::getReceivedData() const
{
    return m_receivedData;
}

void TcpClient::updateGui(QAbstractSocket::SocketState state)
{
    const bool connected = (state == QAbstractSocket::ConnectedState);
    const bool unconnected = (state == QAbstractSocket::UnconnectedState);

}

