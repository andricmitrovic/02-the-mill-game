#ifndef Player_H
#define Player_H

#include "GraphicPiece.h"
#include <string>

/*
 * Klasa Player
 * sadrzi identifikator(iz Nikolinog enuma, to ce nam koristiti za iscrtavanje)
 *        bool promenljivu turn - da li je taj igrac na redu ili ne
 */

class Player {

public:
    Player(const Player& p);
    Player(FIELDSTATE playerID, QString name);

    void changeTurn(); // invertuje bool za turn tog igraca
    QString getName() const;

    // geteri
    bool turn() const;
    FIELDSTATE id() const;
    void incNumOfPieces();
    void decNumOfPieces();
    int getNumOfPieces() const;

private:
    bool m_turn;
    FIELDSTATE m_id;
    int numOfPieces;
    QString name;
};
#endif // Player_H
