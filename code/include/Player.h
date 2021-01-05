#ifndef Player_H
#define Player_H

#include "GraphicPiece.h"
#include <QWidget>
#include <string>

class Player : public QWidget {

public:
    Player(const Player &p);

    Player(FIELDSTATE playerID, QString name);

    void changeTurn();

    bool turn() const;
    FIELDSTATE id() const;
    int getNumOfPieces() const;
    QString getName() const;
    void setId(FIELDSTATE playerId);
    void setTurn(bool turn);

    void incNumOfPieces();
    void decNumOfPieces();

private:
    bool        m_turn;
    FIELDSTATE  m_id;
    int         numOfPieces;
    QString     name;
};
#endif // Player_H
