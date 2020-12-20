#include "gameserver.h"

#include <QHostAddress>

GameServer::GameServer(TcpClient *p1, TcpClient *p2)
        : Game(p1, p2) {

}

void GameServer::serverTest() {
    TcpClient *client1 = static_cast<TcpClient *>(getPlayer1());
    TcpClient *client2 = static_cast<TcpClient *>(getPlayer2());
    if (client1->getSocket()->state() != QAbstractSocket::ConnectedState) {
        client1->getSocket()->connectToHost(QHostAddress::LocalHost, 12345);
        QString message = client1->getName() + QString(": hello there") + QChar(23);
        client1->getSocket()->write(message.toLocal8Bit());

    }
    if (client2->getSocket()->state() != QAbstractSocket::ConnectedState) {
        client2->getSocket()->connectToHost(QHostAddress::LocalHost, 12345);
        client2->getSocket()->waitForReadyRead(1000);
    }
}

void GameServer::playMove(Player *player, int index, QGraphicsScene &scene) {

    if (this->getMillOccured()) {
        //std::cout<< "Mill in playGame"<<std::endl;
        setMessage("Mill in playGame");
        if (removeOpponentsPiece(player, index))
            sendMoveToServer(GAMEMOVE::REMOVE, index, -1);
        this->changeTurn();
        return;
    }

    if (!checkPhase1End()) {
        if (makeSetupMove(player, index, scene)) {
            sendMoveToServer(GAMEMOVE::PLACE, -1, index);
            if (checkMills(index))
                setMillOccured(true);
            else
                this->changeTurn();
        }
    } else if (!gameOver()) {
        if (getMoveFrom() == -1) {
            if (isValidToSelect(index, player))
                setMoveFrom(index);
        } else { // moveFrom != -1
            if (makePlayMove(player, getMoveFrom(), index)) {
                sendMoveToServer(GAMEMOVE::MOVE, getMoveFrom(), index);
                setMoveFrom(-1);
                if (checkMills(index))
                    setMillOccured(true);
                else
                    this->changeTurn();

            } else {
                if (getGameMap()->getBoardFields()[index].getPlayerID() == player->id()) {
                    setMoveFrom(index);
                }
            }
        }
    } else {
        setMessage("Game over!");
        setWinner(getPlayer1()->getNumOfPieces() < getPlayer2()->getNumOfPieces() ? FIELDSTATE::PLAYER_2
                                                                                  : FIELDSTATE::PLAYER_1);
        std::cout << "GAME OVER" << std::endl;
    }
}

void GameServer::sendMoveToServer(GAMEMOVE move, int fromIndex, int toIndex) {
    TcpClient *client1 = static_cast<TcpClient *>(getPlayer1());
    if (client1->getSocket()->state() != QAbstractSocket::ConnectedState) {
        client1->getSocket()->connectToHost(QHostAddress::LocalHost, 12345);
    }
    QString message = client1->getName();
    if (move == GAMEMOVE::MOVE)
        message = message + QString(" ") + QString::number((int) (move)) + QString(" ") + QString::number(fromIndex) +
                  QString(" ") + QString::number(toIndex) + QChar(23);
    if (move == GAMEMOVE::PLACE)
        message = message + QString(" ") + QString::number((int) (move)) + QString(" ") + QString::number(toIndex) +
                  QChar(23);
    if (move == GAMEMOVE::REMOVE)
        message = message + QString(" ") + QString::number((int) (move)) + QString(" ") + QString::number(fromIndex) +
                  QChar(23);

    client1->getSocket()->write(message.toLocal8Bit());
}



void GameServer::getMoveFromServer() {
    TcpClient *client1 = static_cast<TcpClient *>(getPlayer1());
    if (client1->getSocket()->state() != QAbstractSocket::ConnectedState) {
        client1->getSocket()->connectToHost(QHostAddress::LocalHost, 12345);
    }
    client1->getSocket()->waitForReadyRead(1000);
}
