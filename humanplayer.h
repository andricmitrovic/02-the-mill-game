#ifndef HUMANPLAYER_H
#define HUMANPLAYER_H

#include "GraphicPiece.h"
#include <string>

/*
 * Klasa HumanPlayer
 * sadrzi identifikator(iz Nikolinog enuma, to ce nam koristiti za iscrtavanje)
 *        bool promenljivu turn - da li je taj igrac na redu ili ne
 */

class HumanPlayer
{
public:
    HumanPlayer(FIELDSTATE playerID, std::string name);
    HumanPlayer(const HumanPlayer& p);
    void changeTurn(); // invertuje bool za turn tog igraca
    std::string getName() const;

    // geteri
    bool turn() const;
    FIELDSTATE id() const;
    void incNumOfPieces();
    void decNumOfPieces();
    int getNumOfPieces() const;


private:
    FIELDSTATE m_id;
    bool m_turn;
    int numOfPieces;
    std::string name;
};

#endif // HUMANPLAYER_H