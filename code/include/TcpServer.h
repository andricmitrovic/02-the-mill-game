#ifndef TCPSERVER_H
#define TCPSERVER_H

#include <QWidget>
#include <QTcpServer>

class QTcpServer;
class QTcpSocket;

class TcpServer : public QWidget {
    Q_OBJECT

public:
    explicit TcpServer(QWidget *parent = nullptr);

    ~TcpServer();

private slots:
    void newConnection();
    void removeConnection();
    void newMessage();

private:
    QTcpServer                      *m_server;
    QList<QTcpSocket *>             m_clients;
    QHash<QTcpSocket *, QByteArray> m_receivedData;
};
#endif // TCPSERVER_H
