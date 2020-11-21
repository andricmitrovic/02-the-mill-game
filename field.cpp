#include "field.h"
#include <iostream>
/*
 * IMPLEMENTACIJA FIELD klase
 * predstavlja jedno polje na tabeli
 *
 *
 **/
/* postavljanje vrednosti na polje*/
void Field::occupy(VALUE v)
{
    this->occupied = true;
    this->player = v;                   // ovo moze pametnije da nemamo dva ista polja, u piece-u nam treba da bi znali koje boje paintujemo
    this->piece->set_player(v);
}
/* uklanja vrednost sa polja*/
void Field::deoccupy()
{
    this->occupied = false;
    this->player = VALUE::EMPTY;        // isto kao iznad
    this->piece->set_player(VALUE::EMPTY);
}

/*proverava da li je zauzeto*/
bool Field::isOccupied() const
{
    return occupied;
}

/* vraca id (nije dobro ime jer vraca i EMPTY*/
VALUE Field::getPlayerID() const
{
    return player;
}

/* vraca redni broj na tabeli*/
unsigned Field::getFiledPosition() const
{
    return this->positionIndex;
}
/* dodaje susede --- mozda zameniti Variadic metodom, a mozda i ne, jer se koristi samo u konstruktoru*/
void Field::addNeighboursIndices(unsigned p1, unsigned p2)
{
    this->neighboursIndices.push_back(p1);
    this->neighboursIndices.push_back(p2);
}

void Field::addNeighboursIndices(unsigned p1, unsigned p2, unsigned p3)
{
    this->neighboursIndices.push_back(p1);
    this->neighboursIndices.push_back(p2);
    this->neighboursIndices.push_back(p3);
}

void Field::addNeighboursIndices(unsigned p1, unsigned p2, unsigned p3, unsigned p4)
{
    this->neighboursIndices.push_back(p1);
    this->neighboursIndices.push_back(p2);
    this->neighboursIndices.push_back(p3);
    this->neighboursIndices.push_back(p4);
}

