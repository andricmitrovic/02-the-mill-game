#ifndef GAMEMAP_H
#define GAMEMAP_H

#include "field.h"
#include "graphicline.h"

class GameMap
{
public:
    GameMap();
    // metode za ispis
    void printMapTerminal();
    char strPlayer(unsigned p);
    void printMap(QGraphicsScene &scene);
    void printLines(QGraphicsScene &scene);
    void printFields(QGraphicsScene &scene);
    void printFieldTerminal(int index, bool lettersOnly);


    /* Inicijalizuje se za svako polji niz polja koja cine mill*/
    void initilizeMills();
    // vraca indeks polja na osnovu pozicije kvadrata
    int indexByPos(QPointF position);

    // getteri
    int getScale() const;
    int getOffset() const;
    std::vector<Field> &getBoardFields();

private:
    std::vector<Field> boardFields;
    std::vector<GraphicLine*> lines;
    int scale; //distance between the closest two fields in pixels
    int offset;
};

#endif // GAMEMAP_H
