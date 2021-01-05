#ifndef LIB_H
#define LIB_H

#include <iostream>
#include <vector>
#include <string>

#define NUM_OF_PIECES (9)  //number of pieces per player
#define NUM_OF_FIELDS (24) //number of fields on the board
#define NUM_OF_LINES  (16) //number of lines on the board

#define SCALE_MULTIPLIER (20.0) //ratio of the default scale and the window height
#define DEFAULT_SCALE (30.0)    //scale for the defauld window height of 600px

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

enum class GAMEMOVE {
    INIT,
    MOVE,
    PLACE,
    REMOVE,
    GAMEOVER
};
#endif // LIB_H
