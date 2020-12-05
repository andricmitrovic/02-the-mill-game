#ifndef GAMEMAP_H
#define GAMEMAP_H

#include "field.h"
#include "graphicline.h"

class GameMap {

public:
    GameMap();
    // metode za ispis
    void printMapTerminal();
    char strPlayer(unsigned p);
    void printMap(QGraphicsScene &scene);
    void printLines(QGraphicsScene &scene);
    void printFields(QGraphicsScene &scene);
    void initializeLines();
    void initializeFields();
    void printFieldTerminal(int index, bool lettersOnly);

    /* Inicijalizuje se za svako polji niz polja koja cine mill*/
    void initilizeMills();
    // vraca indeks polja na osnovu pozicije kvadrata
    int indexByPos(QPointF position);
    bool inVicinity(float a, float b);

    // getteri
    float getScale() const;
    float getOffset() const;
    std::vector<Field> &getBoardFields();

    void setScale(float scale);
    void recalculateOffset();

private:
    std::vector<Field> boardFields;
    std::vector<GraphicLine*> lines;
    float scale; //distance between the closest two fields in pixels
    float offset;
};

#endif // GAMEMAP_H
