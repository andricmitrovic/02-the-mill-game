#include "gameserver.h"

#include <QHostAddress>

GameServer::GameServer( QWidget *parent, TcpClient *p1, TcpClient *p2)
        :QWidget(parent), Game(p1, p2){

        connect(this->getPlayer1(), SIGNAL(over(GAMEMOVE)), this, SLOT(readMoveFromServer(GAMEMOVE)), Qt::DirectConnection);

}

GameServer::~GameServer()
{

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

    if (player->id() != FIELDSTATE::EMPTY && player->turn()){
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
}

void GameServer::sendMoveToServer(GAMEMOVE move, int fromIndex, int toIndex) {

    TcpClient *client1 = static_cast<TcpClient *>(getPlayer1());

    QString message = client1->getName();
    if (move == GAMEMOVE::MOVE)
        message = message + QString(" ") + QString::number((int) (move)) + QString(" ") + QString::number(fromIndex) +
                  QString(" ") + QString::number(toIndex) + QString(" ") + QChar(23);

    if (move == GAMEMOVE::PLACE)
        message = message + QString(" ") + QString::number((int) (move)) + QString(" ") + QString::number(toIndex) +  QString(" ")
                   +QChar(23);

    if (move == GAMEMOVE::REMOVE)
        message = message + QString(" ") + QString::number((int) (move)) + QString(" ") + QString::number(fromIndex) +
                  QString(" ") + QChar(23);

    client1->getSocket()->write(message.toLocal8Bit());
}

void GameServer::readMoveFromServer(GAMEMOVE move)
{
    TcpClient *client1 = static_cast<TcpClient *>(getPlayer1());
    // ne koristi se za igru, nego samo za pamcenje poteza

    //TcpClient *client2 = static_cast<TcpClient *>(getPlayer2());

    if (move == GAMEMOVE ::INIT){
        client1->setId(FIELDSTATE::PLAYER_2);
        client1->setTurn(false);
    }else if(move == GAMEMOVE :: PLACE){

        FIELDSTATE player_2 = client1->id() == FIELDSTATE::PLAYER_1? FIELDSTATE::PLAYER_2 : FIELDSTATE::PLAYER_1;

        int index = client1->getToIndex();

        this->getGameMap()->getBoardFields()[index].occupy(player_2);

//        client2->incNumOfPieces();

        client1->setTurn(true);
        emit client1->upd();

    }else if(move == GAMEMOVE:: MOVE){

    }else { // move == GAMEMOVE::REMOVE

    }

}
