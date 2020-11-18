#include "gamemap.h"
#include "field.h"
#include "QGraphicsScene"

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
void GameMap::printMap(QGraphicsScene &scene)
{
    boardFields[0].occupy(VALUE::PLAYER_1);
    boardFields[1].occupy(VALUE::PLAYER_2);


    for( int i=0; i<=23; i++)
    {
        scene.addItem(boardFields[i].piece);
        if(boardFields[i].getPlayerID()!=VALUE::EMPTY)
        {
                boardFields[i].piece->setFlag(QGraphicsItem::ItemIsMovable);
                boardFields[i].piece->setFlag(QGraphicsItem::ItemIsSelectable);
        }
    }

    // Ovo ce morati pametnije nekako da bi bilo skalabilno u nekom trenutku
    boardFields[0].piece->setPos(0, 1*30);
    boardFields[1].piece->setPos(0, 7*30);
    boardFields[2].piece->setPos(0, 13*30);

    boardFields[3].piece->setPos(2*30, 3*30);
    boardFields[4].piece->setPos(2*30, 7*30);
    boardFields[5].piece->setPos(2*30, 11*30);

    boardFields[6].piece->setPos(4*30, 5*30);
    boardFields[7].piece->setPos(4*30, 7*30);
    boardFields[8].piece->setPos(4*30, 9*30);

    boardFields[9].piece->setPos(6*30, 1*30);
    boardFields[10].piece->setPos(6*30, 3*30);
    boardFields[11].piece->setPos(6*30, 5*30);
    boardFields[12].piece->setPos(6*30, 9*30);
    boardFields[13].piece->setPos(6*30, 11*30);
    boardFields[14].piece->setPos(6*30, 13*30);

    boardFields[15].piece->setPos(8*30, 5*30);
    boardFields[16].piece->setPos(8*30, 7*30);
    boardFields[17].piece->setPos(8*30, 9*30);

    boardFields[18].piece->setPos(10*30, 3*30);
    boardFields[19].piece->setPos(10*30, 7*30);
    boardFields[20].piece->setPos(10*30, 11*30);

    boardFields[21].piece->setPos(12*30, 1*30);
    boardFields[22].piece->setPos(12*30, 7*30);
    boardFields[23].piece->setPos(12*30, 13*30);

}
