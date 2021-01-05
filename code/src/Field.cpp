#include "code/include/Field.h"

/*
 * Implementation of the class Field
 * Represents one field on the board
*/

/* sets the value on the field*/
void Field::occupy(FIELDSTATE v) {
    this->occupied = true;
    this->player = v;
    this->piece->set_player(v);
}

/* removes the value form the field*/
void Field::deoccupy() {
    this->occupied = false;
    this->player = FIELDSTATE::EMPTY;
    this->piece->set_player(FIELDSTATE::EMPTY);
}

bool Field::isOccupied() const {
    return occupied;
}

FIELDSTATE Field::getPlayerID() const {
    return player;
}

unsigned Field::getFieldPosition() const {
    return this->positionIndex;
}

std::pair <std::pair<unsigned, unsigned>, std::pair<unsigned, unsigned>> Field::getMills() const {
    return this->mills;
}

void Field::addMills(unsigned a1, unsigned a2, unsigned b1, unsigned b2) {
    std::pair<unsigned, unsigned> mill1;
    mill1.first = a1;
    mill1.second = a2;
    this->mills.first = mill1;

    std::pair<unsigned, unsigned> mill2;
    mill2.first = b1;
    mill2.second = b2;
    this->mills.second = mill2;
}

void Field::addNeighboursIndices(unsigned p1, unsigned p2) {
    this->neighboursIndices.push_back(p1);
    this->neighboursIndices.push_back(p2);
}

void Field::addNeighboursIndices(unsigned p1, unsigned p2, unsigned p3) {
    this->neighboursIndices.push_back(p1);
    this->neighboursIndices.push_back(p2);
    this->neighboursIndices.push_back(p3);
}

void Field::addNeighboursIndices(unsigned p1, unsigned p2, unsigned p3, unsigned p4) {
    this->neighboursIndices.push_back(p1);
    this->neighboursIndices.push_back(p2);
    this->neighboursIndices.push_back(p3);
    this->neighboursIndices.push_back(p4);
}

std::vector<unsigned> Field::getNeighboursIndices() const {
    return neighboursIndices;
}
