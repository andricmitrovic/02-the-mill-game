#ifndef GAMEMAP_H
#define GAMEMAP_H

#include "field.h"

class GameMap
{
public:
    GameMap();
    // printMap i strPlayer za ispisivanje u terminalu
    void printMap(QGraphicsScene &scene);
    char strPlayer(unsigned p);
    /* Inicijalizuje se za svako polji niz polja koja cine mill*/
    void initilizeMills();


public:
// niz polja
std::vector<Field> boardFields;
// broj postavljenih pakova za svakog igrace
int numofpieces1;
int numofpieces2;
};

#endif // GAMEMAP_H
