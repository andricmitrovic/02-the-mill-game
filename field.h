#ifndef FIELD_H
#define FIELD_H

#include <vector>
#include "GraphicPiece.h"


class Field {

public:
    Field(unsigned position)
        :player(FIELDSTATE::EMPTY), occupied(false),positionIndex(position)
    {
    //neighboursIndices = std::vector<unsigned>();
        piece = new GraphicPiece();
    }

    void deoccupy();
    void occupy(FIELDSTATE p);
    bool isOccupied() const;
    FIELDSTATE getPlayerID() const;
    unsigned getFieldPosition() const;
    std::pair<std::pair<unsigned, unsigned>, std::pair<unsigned, unsigned>> getMills() const;
    void addMills(unsigned a1, unsigned a2, unsigned b1, unsigned b2);
    void addNeighboursIndices(unsigned p1, unsigned p2);
    void addNeighboursIndices(unsigned p1, unsigned p2, unsigned p3);
    void addNeighboursIndices(unsigned p1, unsigned p2, unsigned p3, unsigned p4);
    std::vector<unsigned> getNeighboursIndices() const;
    // sluzi za iscrtavanje kockice
    GraphicPiece *piece;              // geter seter i private da bude, a iskreno i ne mora jer se koristi u okviru druge klase samo

private:
    FIELDSTATE player;
    bool occupied;
    unsigned positionIndex;
    std::vector<unsigned> neighboursIndices;
    std::pair<std::pair<unsigned, unsigned>, std::pair<unsigned, unsigned>> mills; //Every field has only two mills, which consist of 3 fields.
};

#endif // FIELD_H
