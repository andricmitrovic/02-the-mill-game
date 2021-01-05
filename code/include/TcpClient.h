#ifndef TCPCLIENT_H
#define TCPCLIENT_H

#include <QAbstractSocket>
#include <QJsonDocument>
#include <QTcpSocket>
#include <QWidget>

#include "Player.h"

class TcpClient;

class TcpClient : public Player
{
    Q_OBJECT

public:
    explicit TcpClient(FIELDSTATE playerId, QString playerName);
    ~TcpClient();
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
    void over(GAMEMOVE move);
    void upd();

private:
    QTcpSocket *m_socket;
    //QString m_receivedData;
    QJsonDocument m_receivedData_1;
    int fromIndex;
    int toIndex;
    GAMEMOVE move;
public:
    bool m_gameStart;
    bool m_millOccured;
};

#endif // TCPCLIENT_H
