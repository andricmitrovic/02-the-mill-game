#ifndef GAME_H
#define GAME_H

#include "GameMap.h"
#include "Player.h"
#include "Lib.h"

class Game {

public:

    Game(Player *p1, Player *p2, GAMEMODE gameMode);

    ~Game();

    void changeTurn();
    virtual void playMove(Player *player, int index, MyGraphicsScene *scene);
    bool makeSetupMove(Player *player, unsigned i, MyGraphicsScene *scene);
    bool fconentsPiece(Player *player, unsigned index);
    bool makePlayMove(Player *player, unsigned moveFrom, unsigned moveTo);
    bool removeOpponentsPiece(Player *player, unsigned index);

    bool gameOver();
    bool checkPhase1End();
    bool checkMills(unsigned index) const;
    bool hasAvailableFields(Player *player) const;

    bool isValidToMove(int from, int to) const;
    bool isValidToRemove(int i, Player *player, bool displayError = 1);
    bool isValidToSelect(int i, Player *player) const;

    QString getGameMessage() const;
    QString getErrorMessage() const;
    FIELDSTATE getWinner() const;
    Player *getCurrentPlayer();
    GameMap *getGameMap() const;
    Player *getPlayer1() const;
    Player *getPlayer2() const;
    GAMESTATE getGameState();
    bool getMillOccurred();
    int getMoveFrom();
    int getBoardPieces();

    void setWinner(FIELDSTATE winner);
    void setGameMessage(const std::string &msg);
    void setErrorMessage(const std::string &msg);
    void clearGameMessage();
    void clearErrorMessage();
    void setGameMap(GameMap *gameMap);
    void setPlayer1(Player *p1);
    void setPlayer2(Player *p2);
    void setGameState(GAMESTATE gameState);
    void setMillOccurred(bool millOccurred);
    void setMoveFrom(int moveFrom);
    void setBoardPieces(int boardPieces);

private:
    GameMap     *gameMap;
    Player      *m_p1;
    Player      *m_p2;
    GAMESTATE   gameState;
    FIELDSTATE  winner;
    GAMEMODE    gameMode;
    QString     gameMessage;
    QString     errorMessage;
    bool        millOccurred;
    int         moveFrom;
    int         boardPieces;
};
#endif // GAME_H
