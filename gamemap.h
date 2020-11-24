#ifndef GAMEMAP_H
#define GAMEMAP_H

#include "field.h"

class GameMap
{
public:
    GameMap();
    // printMap i strPlayer za ispisivanje u terminalu
    void printMap(QGraphicsScene &scene);
    void printFieldTerminal(int index, bool lettersOnly);
    void printMapTerminal();
    char strPlayer(unsigned p);
    /* Inicijalizuje se za svako polji niz polja koja cine mill*/
    void initilizeMills();
    // vraca indeks polja na osnovu pozicije kvadrata
    int indexByPos(QPointF position);


    /* napraviti da bude private + getter*/
public:
// niz polja
std::vector<Field> boardFields;
};

#endif // GAMEMAP_H
