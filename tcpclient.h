#ifndef TCPCLIENT_H
#define TCPCLIENT_H

#include <QAbstractSocket>
#include <QTcpSocket>
#include <QWidget>

#include "player.h"

class TcpClient;

class TcpClient : public Player
{
    Q_OBJECT

public:
    explicit TcpClient(FIELDSTATE playerId, QString playerName);
    QTcpSocket* getSocket() const;
    QString getReceivedData() const;
    int getFromIndex() const;
    int getToIndex() const;
    GAMEMOVE getMove() const;

    void setFromIndex(int value);
    void setToIndex(int value);
    void setMove(GAMEMOVE value);

public slots:
    void readMessage();
    void onReadFinished();

signals:
    void readFinished();

private:
    QTcpSocket *m_socket;
    QString m_receivedData;
    int fromIndex;
    int toIndex;
    GAMEMOVE move;
};

#endif // TCPCLIENT_H
