#ifndef GAMEMAP_H
#define GAMEMAP_H

#include "Field.h"
#include "Piece.h"
#include "GraphicLine.h"
#include "MyGraphicsScene.h"

class GameMap {

public:
    GameMap();
    ~GameMap();
    // metode za ispis
    void printMapTerminal();
    char strPlayer(unsigned p);
    void printMap(MyGraphicsScene *scene);
    void printLines(MyGraphicsScene *scene);
    void printFields(MyGraphicsScene *scene);
    void printPieces(MyGraphicsScene *scene);
    void initializeLines();
    void initializeFields();
    void initializePieces();
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
    std::vector<Piece*> &getRedPieces();
    std::vector<Piece*> &getBluePieces();

    void setScale(float scale);
    void recalculateOffset();

private:
    std::vector<Field> boardFields;
    std::vector<GraphicLine*> lines;
    std::vector<Piece*> redPieces;
    std::vector<Piece*> bluePieces;
    float scale; //distance between the closest two fields in pixels
    float offset;
    int removeIndex = 0;
};

#endif // GAMEMAP_H
