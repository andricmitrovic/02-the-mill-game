#ifndef TCPSERVER_H
#define TCPSERVER_H

#include <QWidget>
#include <QTcpServer>

namespace Ui {
class TcpServer;
}

class QTcpServer;
class QTcpSocket;

class TcpServer : public QWidget
{
    Q_OBJECT

public:
    explicit TcpServer(QWidget *parent = 0);
    ~TcpServer();

private slots:
    void newConnection();
    void removeConnection();
    void newMessage();

    void on_disconnectClients_clicked();

private:
    Ui::TcpServer *ui;
    QTcpServer *m_server;
    QList<QTcpSocket*> m_clients;
    QHash<QTcpSocket*, QString> m_receivedData;
};

#endif // TCPSERVER_H
