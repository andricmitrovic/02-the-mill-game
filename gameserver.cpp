#include "gameserver.h"

#include <QHostAddress>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonValue>

GameServer::GameServer( QWidget *parent, TcpClient *p1, TcpClient *p2)
        :QWidget(parent), Game(p1, p2){

        connect(this->getPlayer1(), SIGNAL(over(GAMEMOVE)), this, SLOT(readMoveFromServer(GAMEMOVE)), Qt::DirectConnection);

}

GameServer::~GameServer()
{

}

void GameServer::playMove(Player *player, int index, QGraphicsScene &scene) {



    if (player->id() != active || !player->turn()){
        setMessage("It's not your turn yet! :(");
        return ;

    }

    if (this->getMillOccured()) {
        setMessage("Mill in playGame");

        if (removeOpponentsPiece(player, index)){
            if (checkPhase1End() && gameOver()){
                setMessage("GAME OVER! YOU WON!");
                sendMoveToServer(GAMEMOVE::REMOVE, index, -1);
                sendMoveToServer(GAMEMOVE::GAMEOVER, -1, -1);
            }else{
                this->changeTurn();
                sendMoveToServer(GAMEMOVE::REMOVE, index, -1);
            }
        }

        return;
    }

    if (!checkPhase1End()) {

        if (makeSetupMove(player, index, scene)) {
            if (checkMills(index)){
                setMillOccured(true);
                sendMoveToServer(GAMEMOVE::PLACE, -1, index);

            }
            else{
                sendMoveToServer(GAMEMOVE::PLACE, -1, index);
                this->changeTurn();
            }


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
        setMessage("Game over! YOU WON!");
        setWinner(getPlayer1()->getNumOfPieces() < getPlayer2()->getNumOfPieces() ? FIELDSTATE::PLAYER_2
                                                                                  : FIELDSTATE::PLAYER_1);
        sendMoveToServer(GAMEMOVE :: GAMEOVER, -1, -1);
    }

}

void GameServer::sendMoveToServer(GAMEMOVE move, int fromIndex, int toIndex) {

    TcpClient *client1 = static_cast<TcpClient *>(getPlayer1());

    QString message = client1->getName();
    QJsonObject message1 = QJsonObject();



    message1.insert(QString("name"), QJsonValue(client1->getName()));
    if (move == GAMEMOVE :: GAMEOVER){
        message1.insert(QString("game_move"), QJsonValue(static_cast<int>(move)));

    } else {

        message1.insert(QString("toIndex"), QJsonValue(toIndex));
        message1.insert(QString("FromIndex"), QJsonValue(fromIndex));
        message1.insert(QString("mill_occured"), QJsonValue(getMillOccured()));
        message1.insert(QString("game_move"), QJsonValue(static_cast<int>(move)));


    }
    client1->getSocket()->write(QJsonDocument(message1).toJson());
}

void GameServer::readMoveFromServer(GAMEMOVE move)
{
    TcpClient *client1 = static_cast<TcpClient *>(getPlayer1());
    // ne koristi se za igru, nego samo za pamcenje poteza
    TcpClient *client2 = static_cast<TcpClient *>(getPlayer2());

    if (move == GAMEMOVE ::INIT){

        this->active = client1->id();

        client2->setId(client1->id() == FIELDSTATE:: PLAYER_1? FIELDSTATE::PLAYER_2 :FIELDSTATE :: PLAYER_1);

        client1->turn() ? client2->setTurn(false) : client2->setTurn(true);

    }else {
        emit client1->upd();

    }


}
