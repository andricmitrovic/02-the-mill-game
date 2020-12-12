#ifndef TCPCLIENT_H
#define TCPCLIENT_H

#include <QWidget>
#include <QAbstractSocket>

#include "humanplayer.h"

class QTcpSocket;

class TcpClient;

class TcpClient : public QWidget
{
    Q_OBJECT

public:
    explicit TcpClient(FIELDSTATE playerId, QString playerName);
    ~TcpClient();
    HumanPlayer getPlayer();

private slots:
//    void on_text_returnPressed();
    void readMessage();
//    void on_connect_clicked();
    void connectedToServer();
//    void on_disconnect_clicked();
    void disconnectByServer();

private:
    QTcpSocket *m_socket;
    HumanPlayer m_player;
    QString m_receivedData;

    void updateGui(QAbstractSocket::SocketState state);
};

#endif // TCPCLIENT_H
