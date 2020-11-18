#ifndef FIELD_H
#define FIELD_H

#include <vector>

#include "GraphicPiece.h"


class Field
{
public:
    Field(unsigned position)
        :player(VALUE::EMPTY), occupied(false),positionIndex(position)
    {
    //neighboursIndices = std::vector<unsigned>();
        piece = new GraphicPiece();
    }

    void deoccupy();
    void occupy(VALUE p);
    bool isOccupied() const;
    VALUE getPlayerID() const;
    unsigned getFiledPosition() const;
    void addNeighboursIndices(unsigned p1, unsigned p2);
    void addNeighboursIndices(unsigned p1, unsigned p2, unsigned p3);
    void addNeighboursIndices(unsigned p1, unsigned p2, unsigned p3, unsigned p4);

    // sluzi za iscrtavanje kockice
    GraphicPiece *piece;              // geter seter i private da bude, a iskreno i ne mora jer se koristi u okviru druge klase samo

private:

    VALUE player;
    bool occupied;
    unsigned positionIndex;
    std::vector<unsigned> neighboursIndices;


};

#endif // FIELD_H
