#ifndef FIELD_H
#define FIELD_H

#include <vector>
#include "GraphicPiece.h"

class Field {

public:
    Field(unsigned position)
            : occupied(false), player(FIELDSTATE::EMPTY), positionIndex(position) {
        piece = new GraphicPiece();
    }

    void deoccupy();
    bool isOccupied() const;
    void occupy(FIELDSTATE p);

    FIELDSTATE getPlayerID() const;
    unsigned getFieldPosition() const;
    std::vector<unsigned> getNeighboursIndices() const;
    std::pair<std::pair<unsigned, unsigned>, std::pair<unsigned, unsigned>> getMills() const;

    void addNeighboursIndices(unsigned p1, unsigned p2);
    void addNeighboursIndices(unsigned p1, unsigned p2, unsigned p3);
    void addNeighboursIndices(unsigned p1, unsigned p2, unsigned p3, unsigned p4);
    void addMills(unsigned a1, unsigned a2, unsigned b1, unsigned b2);

    GraphicPiece *piece;

private:
    bool                                                                    occupied;
    FIELDSTATE                                                              player;
    unsigned                                                                positionIndex;
    std::vector<unsigned>                                                   neighboursIndices;
    std::pair<std::pair<unsigned, unsigned>, std::pair<unsigned, unsigned>> mills; //Every field has only two mills, which consist of 3 fields.
};
#endif // FIELD_H
