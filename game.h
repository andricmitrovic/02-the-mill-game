#ifndef GAME_H
#define GAME_H

#include "gamemap.h"
#include "player.h"
#include "lib.h"

/*
 * Klasa Game
 * sadrzi GameMap (mapa koju je Marija pravila koja sadrzi vektor svih polja)
 *        dva igraca (za sada su oba Player)
 */

class Game {
public:

    Game(Player* p1, Player* p2);
    ~Game();

    // metode
    void setup_graphical();

    void changeTurn();
    virtual void playMove(Player*  player, int index, QGraphicsScene &scene); // ova bi trebalo da se postavi na virtual

    bool makeSetupMove(Player* player, unsigned i, QGraphicsScene &scene);
    bool fconentsPiece(Player*  player, unsigned index);
    bool makePlayMove(Player* player, unsigned moveFrom, unsigned moveTo);
    bool removeOpponentsPiece(Player* player, unsigned index);

    // metodi za proveru stanje igre
    bool gameOver();
    bool checkPhase1End();
    bool checkMills(unsigned index) const;

    //provera indeks
    bool isValidIndex(int i) const;
    bool isValidToMove(int from, int to) const;
    bool isValidToRemove(int i, Player*  player);
    bool isValidToSelect(int i, Player*  player) const;

    // getteri
    QString getMessage() const;
    FIELDSTATE getWinner() const;
    Player* getCurrentPlayer();
    GameMap *getGameMap() const;
    Player* getPlayer1() const;
    Player* getPlayer2() const;
    GAMESTATE getGameState();
    bool getMillOccured();
    int getMoveFrom();
    int getBoardPieces();

    // setteri
    void setWinner(FIELDSTATE winner);
    void setMessage(const std::string &msg);
    void setGameMap(GameMap *gameMap);
    void setPlayer1(Player* p1);
    void setPlayer2(Player* p2);
    void setGameState(GAMESTATE gameState);
    void setMillOccured(bool millOccured);
    void setMoveFrom(int moveFrom);
    void setBoardPieces(int boardPieces);

private:  
    GameMap         *gameMap;
    Player          *m_p1;
    Player          *m_p2;
    GAMESTATE       gameState;
    FIELDSTATE      winner;
    QString         message;
    bool            millOccured;
    int             moveFrom;
    int             boardPieces;
};

#endif // GAME_H
