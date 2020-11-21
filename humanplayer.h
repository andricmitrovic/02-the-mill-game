#ifndef HUMANPLAYER_H
#define HUMANPLAYER_H

#include "GraphicPiece.h"


/*
 * Klasa HumanPlayer
 * sadrzi identifikator(iz Nikolinog enuma, to ce nam koristiti za iscrtavanje)
 *        bool promenljivu turn - da li je taj igrac na redu ili ne
 */

class HumanPlayer
{
public:
    HumanPlayer(VALUE playerID);
    void changeTurn(); // invertuje bool za turn tog igraca

    // geteri
    bool turn() const;
    VALUE id() const;


private:
    VALUE m_id;
    bool m_turn = false;
};

#endif // HUMANPLAYER_H
