#ifndef GAMEMAP_H
#define GAMEMAP_H

#include "field.h"
#include "graphicline.h"
#include "piece.h"

class GameMap {

public:
    GameMap();
    // metode za ispis
    void printMapTerminal();
    char strPlayer(unsigned p);
    void printMap(QGraphicsScene &scene);
    void printLines(QGraphicsScene &scene);
    void printFields(QGraphicsScene &scene);
    void printPieces(QGraphicsScene &scene);
    void initializeLines();
    void initializeFields();
    void initializePieces();
    void removePiece(QGraphicsScene &scene, int index);
    void printFieldTerminal(int index, bool lettersOnly);

    /* Inicijalizuje se za svako polji niz polja koja cine mill*/
    void initilizeMills();
    // vraca indeks polja na osnovu pozicije kvadrata
    int indexByPos(QPointF position);
    bool inVicinity(float a, float b);

    // getteri
    float getScale() const;
    float getOffset() const;
    int getRemoveIndex();
    std::vector<Field> &getBoardFields();
    std::vector<Piece*> &getPieces();

    void setScale(float scale);
    void recalculateOffset();
    void incRemoveIndex();


private:
    std::vector<Field> boardFields;
    std::vector<GraphicLine*> lines;
    std::vector<Piece*> pieces;
    float scale; //distance between the closest two fields in pixels
    float offset;
    int removeIndex = 0;
};

#endif // GAMEMAP_H
