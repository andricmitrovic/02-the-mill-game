#ifndef FIELD_H
#define FIELD_H

#include <vector>

enum class VALUE
{
    EMPTY,
    PLAYER_1,
    PLAYER_2
};

class Field
{
public:
    Field(unsigned position)
        :player(VALUE::EMPTY), occupied(false),positionIndex(position)
    {
    //neighboursIndices = std::vector<unsigned>();
    }

    void deoccupy();
    void occupy(VALUE p);
    bool isOccupied() const;
    VALUE getPlayerID() const;
    unsigned getFiledPosition() const;
    void addNeighboursIndices(unsigned p1, unsigned p2);
    void addNeighboursIndices(unsigned p1, unsigned p2, unsigned p3);
    void addNeighboursIndices(unsigned p1, unsigned p2, unsigned p3, unsigned p4);
private:

    VALUE player;
    bool occupied;
    unsigned positionIndex;
    std::vector<unsigned> neighboursIndices;

};

#endif // FIELD_H
