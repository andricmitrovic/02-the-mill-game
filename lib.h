#ifndef LIB_H
#define LIB_H

#include <iostream>
#include <vector>
#include <string>


#define NUM_OF_PIECES (9) //broj figura po igracu
#define NUM_OF_FIELDS (24) // broj polja na mapi


enum class FIELDSTATE
{
    EMPTY,
    PLAYER_1,
    PLAYER_2
};


enum class GAMESTATE
{
    INIT,
    PLAY
};

#endif // LIB_H
