#include "humanplayer.h"

HumanPlayer::HumanPlayer(FIELDSTATE playerID, std::string name):m_turn(false),  m_id(playerID), numOfPieces(0), name(std::string(name)) {}

// copy konstruktor
HumanPlayer::HumanPlayer(const HumanPlayer & p): m_turn(p.turn()), m_id(p.id()), numOfPieces(p.getNumOfPieces()), name(p.getName()) {}

void HumanPlayer::changeTurn() {
    m_turn = !m_turn;
}

std::string HumanPlayer::getName() const {
    return this -> name;
}

bool HumanPlayer::turn() const {
    return m_turn;
}

FIELDSTATE HumanPlayer::id() const {
    return m_id;
}

void HumanPlayer::incNumOfPieces() {
    this -> numOfPieces++;
}

void HumanPlayer::decNumOfPieces() {
    this -> numOfPieces--;
}

int HumanPlayer::getNumOfPieces() const {
    return numOfPieces;
}
