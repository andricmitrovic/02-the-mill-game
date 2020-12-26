#include "player.h"

Player::Player(FIELDSTATE playerID, QString name)
    :m_turn(false),  m_id(playerID), numOfPieces(0), name(QString(name))
{}

// copy konstruktor
Player::Player(const Player & p)
    :m_turn(p.turn()), m_id(p.id()), numOfPieces(p.getNumOfPieces()), name(p.getName())
{}

void Player::changeTurn() {
    m_turn = !m_turn;
}

QString Player::getName() const {
    return this -> name;
}

bool Player::turn() const {
    return m_turn;
}

FIELDSTATE Player::id() const {
    return m_id;
}

void Player::incNumOfPieces() {
    this -> numOfPieces++;
}

void Player::decNumOfPieces() {
    this -> numOfPieces--;
}

int Player::getNumOfPieces() const {
    return numOfPieces;
}

void Player::setId(FIELDSTATE playerId)
{
    this->m_id = playerId;
}

void Player::setTurn(bool turn)
{
    this->m_turn = turn;
}


