#ifndef GAME_H
#define GAME_H

#include "GameMap.h"
#include "Player.h"
#include "Lib.h"

/*
 * Klasa Game
 * sadrzi GameMap (mapa koju je Marija pravila koja sadrzi vektor svih polja)
 *        dva igraca (za sada su oba Player)
 */

class Game {

public:

    Game(Player* p1, Player* p2, GAMEMODE gameMode);
    ~Game();

    // metode
    void changeTurn();
    virtual void playMove(Player*  player, int index, MyGraphicsScene *scene); // ova bi trebalo da se postavi na virtual

    bool makeSetupMove(Player* player, unsigned i, MyGraphicsScene *scene);
    bool fconentsPiece(Player*  player, unsigned index);
    bool makePlayMove(Player* player, unsigned moveFrom, unsigned moveTo);
    bool removeOpponentsPiece(Player* player, unsigned index);

    // metodi za proveru stanje igre
    bool gameOver();
    bool checkPhase1End();
    bool checkMills(unsigned index) const;
    bool hasAvailableFields(Player *player) const;

    //provera indeks
    bool isValidToMove(int from, int to) const;
    bool isValidToRemove(int i, Player*  player,  bool displayError = 1);
    bool isValidToSelect(int i, Player*  player) const;

    // getteri
    QString getGameMessage() const;
    QString getErrorMessage() const;
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
    void setGameMessage(const std::string &msg);
    void clearGameMessage();
    void setErrorMessage(const std::string &msg);
    void clearErrorMessage();
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
    GAMEMODE        gameMode;
    QString         gameMessage;
    QString         errorMessage;
    bool            millOccured;
    int             moveFrom;
    int             boardPieces;
};

#endif // GAME_H
