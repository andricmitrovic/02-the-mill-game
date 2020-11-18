#include "gamemap.h"
#include "field.h"

#include <vector>
#include <string>
#include <iostream>

#define NUM_OF_FIELDS 24

/* GameMap klasa koja implementira mapu igre
 *
 * POLJA KLASE:
 *  -> niza polja (klasa Field -- detaljnije u field)
 * NUMERACIJA POLJA U MAPI
 *  0 - - - - - 1 - - - - - 2
 *  |           |           |
 *  |     3 - - 4 - - 5     |
 *  |     |     |     |     |
 *  |     | 6 - 7 - 8 |     |
 *  |     | |       | |     |
 *  9 - -10-11    12- 13- - 14
 *  |     | |       | |     |
 *  |     |15 - 16 -17|     |
 *  |     |     |     |     |
 *  |     18 - -19 - -20    |
 *  |           |           |
 *  21 - - - - -22 - - - - - 23
 *
 *
 * */
GameMap::GameMap():
    numofpieces1(0), numofpieces2(0)
{
        // Inicijalizacija polja na tabeli
        for(int i = 0; i < NUM_OF_FIELDS; i++) {
                boardFields.push_back(Field(i));
        }


        // Azuriranje liste suseda za svako polje

        boardFields[0].addNeighboursIndices(1,9);
        boardFields[1].addNeighboursIndices(0,2,4);
        boardFields[2].addNeighboursIndices(1,14);

        boardFields[3].addNeighboursIndices(4,10);
        boardFields[4].addNeighboursIndices(1,3,5,7);
        boardFields[5].addNeighboursIndices(4,13);

        boardFields[6].addNeighboursIndices(7,11);
        boardFields[7].addNeighboursIndices(4,6,8);
        boardFields[8].addNeighboursIndices(7,12);

        boardFields[9].addNeighboursIndices(0,10,21);
        boardFields[10].addNeighboursIndices(3,9,11,18);
        boardFields[11].addNeighboursIndices(6,10,15);

        boardFields[12].addNeighboursIndices(8,13,17);
        boardFields[13].addNeighboursIndices(5,12,14,20);
        boardFields[14].addNeighboursIndices(2,13,23);

        boardFields[15].addNeighboursIndices(11,16);
        boardFields[16].addNeighboursIndices(15,17,19);
        boardFields[17].addNeighboursIndices(12,16);

        boardFields[18].addNeighboursIndices(10,19);
        boardFields[19].addNeighboursIndices(16,18,20,22);
        boardFields[20].addNeighboursIndices(13,19);

        boardFields[21].addNeighboursIndices(9,22);
        boardFields[22].addNeighboursIndices(19,21,23);
        boardFields[23].addNeighboursIndices(14,22);

}
void GameMap::printMap() {
        std::cout << strPlayer(0)<< " - - - - - " << strPlayer(1) << " - - - - - "<< strPlayer(2)<< std::endl;
        std::cout <<"|           |           |" <<std::endl;
        std::cout <<"|     "<<strPlayer(3)<<" - - "<<strPlayer(4)<<" - - "<<strPlayer(5)<<"     |"<<std::endl;
        std::cout <<"|     |     |     |     |"<<std::endl;
        std::cout <<"|     | "<<strPlayer(6)<<" - "<<strPlayer(7)<<" - "<<strPlayer(8)<<" |     |" <<std::endl;
        std::cout <<"|     | |       | |     |"<<std::endl;
        std::cout <<strPlayer(9)<<" - - "<<strPlayer(10)<<"-"<<strPlayer(11)<<"       "<<strPlayer(12)<<"-"<<strPlayer(13)<<" - - "<<strPlayer(14)<<std::endl;
        std::cout <<"|     | |       | |     |"<<std::endl;
        std::cout <<"|     | "<<strPlayer(15)<<" - "<<strPlayer(16)<<" - "<<strPlayer(17)<<" |     |" <<std::endl;
        std::cout <<"|     |     |     |     |"<<std::endl;
        std::cout <<"|     "<<strPlayer(18)<<" - - "<<strPlayer(19)<<" - - "<<strPlayer(20)<<"     |"<<std::endl;
        std::cout <<"|           |           |"<<std::endl;
        std::cout <<strPlayer(21)<<" - - - - - "<<strPlayer(22)<<" - - - - - "<<strPlayer(23)<<std::endl;
}

char GameMap::strPlayer(unsigned pos)
{
    VALUE v = boardFields[pos].getPlayerID();
    switch(v){
    case VALUE::EMPTY :
        return 'X';
    case VALUE::PLAYER_1:
        return '1';
    case VALUE::PLAYER_2:
        return '2';

    }
    return 'X';
}

// MAIN ZA TESTIRANJE

/*
int main()
{
    GameMap gm = GameMap();
    gm.printMap();
    return 0;
}
*/


