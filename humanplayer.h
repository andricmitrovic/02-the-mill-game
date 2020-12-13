#ifndef HUMANPLAYER_H
#define HUMANPLAYER_H

#include "GraphicPiece.h"
#include <string>

/*
 * Klasa HumanPlayer
 * sadrzi identifikator(iz Nikolinog enuma, to ce nam koristiti za iscrtavanje)
 *        bool promenljivu turn - da li je taj igrac na redu ili ne
 */

class HumanPlayer {

public:
    HumanPlayer(const HumanPlayer& p);
    HumanPlayer(FIELDSTATE playerID, QString name);

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
#endif // HUMANPLAYER_H
