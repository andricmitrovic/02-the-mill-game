#ifndef GAMESERVER_H
#define GAMESERVER_H


#include "gamemap.h"
#include "tcpclient.h"
#include "lib.h"

class GameServer {
public:

    GameServer(TcpClient& p1, TcpClient& p2);
    ~GameServer();

    // metode
    QString serverTest();
    void play(); // ovo je igranje igre, odnosno premestanje vec postavljenih figura
    void setup(); // ovo je postavljanje figura, tj. prva faza igre
    void setup_graphical();

    void changeTurn();
    bool makePlayMove(TcpClient& player);
    bool makeSetupMove(TcpClient& player);
    void playMove(TcpClient& player, int index, QGraphicsScene &scene);
    void removeOpponentsPiece(TcpClient& player);

    bool makeSetupMove_graphical(TcpClient &player, unsigned i, QGraphicsScene &scene);
    bool removeOpponentsPiece_graphic(TcpClient& player, unsigned index);
    bool makePlayMove_graphical(TcpClient &player, unsigned moveFrom, unsigned moveTo);

    // metodi za proveru stanje igre
    bool gameOver();
    bool checkPhase1End();
    bool checkMills(unsigned index) const;

    //provera indeks

    bool isValidIndex(int i) const;
    bool isValidToMove(int from, int to) const;
    bool isValidToRemove(int i, TcpClient& player);
    bool isValidToSelect(int i, TcpClient& player) const;
    bool isValidToOccupy(int i, TcpClient& player) const;

    // getteri
    QString getMessage() const;
    FIELDSTATE getWinner() const;
    TcpClient &getCurrentPlayer();

    // setteri
    void setWinner(FIELDSTATE winner);
    void setMessage(const std::string &msg);

    // seteri i geteri za ovo sve
    GameMap         *gameMap;               // i ovo mi treba public
    TcpClient       m_p1;                   // stavio sam public jer mi treba turn metoda nad ovim objektima
    TcpClient       m_p2;                   // public
    int             phase1_piece_counter;   // dodao ovo ovde da bi iz boarda znao kada da prekinem prvi deo igre
    GAMESTATE       gameState;
    bool            mill_occured;
    int             moveFrom;
    int             boardPieces;



private:
    FIELDSTATE      winner;
    QString         message;

};
#endif // GAMESERVER_H
