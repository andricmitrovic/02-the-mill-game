#ifndef LIB_H
#define LIB_H

#include <iostream>
#include <vector>
#include <string>

#define NUM_OF_PIECES (9) //broj figura po igracu
#define NUM_OF_FIELDS (24) // broj polja na mapi
#define NUM_OF_LINES  (16) // broj linija na mapi

#define SCALE_MULTIPLIER (20.0)
#define DEFAULT_SCALE (30.0)

enum class FIELDSTATE {
    EMPTY,
    PLAYER_1,
    PLAYER_2
};


enum class GAMESTATE {
    INIT,
    PLAY
};

enum class GAMEMODE {
    LOCAL,
    AI,
    SERVER
};

#endif // LIB_H
