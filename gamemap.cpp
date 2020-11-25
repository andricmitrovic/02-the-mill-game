#include "gamemap.h"
#include "field.h"
#include "QGraphicsScene"



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
 *  21 - - - - -22 - - - - - 23*/
GameMap::GameMap()

    {
    // Inicijalizacija polja na tabeli
    for (int i = 0; i < NUM_OF_FIELDS; i++) {
        boardFields.push_back(Field(i));
    }

    // Azuriranje liste suseda za svako polje

    boardFields[0].addNeighboursIndices(1, 9);
    boardFields[1].addNeighboursIndices(0, 2, 4);
    boardFields[2].addNeighboursIndices(1, 14);

    boardFields[3].addNeighboursIndices(4, 10);
    boardFields[4].addNeighboursIndices(1, 3, 5, 7);
    boardFields[5].addNeighboursIndices(4, 13);

    boardFields[6].addNeighboursIndices(7, 11);
    boardFields[7].addNeighboursIndices(4, 6, 8);
    boardFields[8].addNeighboursIndices(7, 12);

    boardFields[9].addNeighboursIndices(0, 10, 21);
    boardFields[10].addNeighboursIndices(3, 9, 11, 18);
    boardFields[11].addNeighboursIndices(6, 10, 15);

    boardFields[12].addNeighboursIndices(8, 13, 17);
    boardFields[13].addNeighboursIndices(5, 12, 14, 20);
    boardFields[14].addNeighboursIndices(2, 13, 23);

    boardFields[15].addNeighboursIndices(11, 16);
    boardFields[16].addNeighboursIndices(15, 17, 19);
    boardFields[17].addNeighboursIndices(12, 16);

    boardFields[18].addNeighboursIndices(10, 19);
    boardFields[19].addNeighboursIndices(16, 18, 20, 22);
    boardFields[20].addNeighboursIndices(13, 19);

    boardFields[21].addNeighboursIndices(9, 22);
    boardFields[22].addNeighboursIndices(19, 21, 23);
    boardFields[23].addNeighboursIndices(14, 22);

    initilizeMills();
}

void GameMap::printMap(QGraphicsScene &scene) {

    for (unsigned i = 0u; i < NUM_OF_FIELDS; i++) {
        scene.addItem(boardFields[i].piece);
        boardFields[i].piece->setFlag(QGraphicsItem::ItemIsSelectable);
    }

    // !!!!!! Ovo ce morati pametnije nekako da bi bilo skalabilno u nekom trenutku !!!!!!
    boardFields[0].piece->setPos(0, 1 * 30);
    boardFields[1].piece->setPos(6 * 30, 1 * 30);
    boardFields[2].piece->setPos(12 * 30, 1 * 30);

    boardFields[3].piece->setPos(2 * 30, 3 * 30);
    boardFields[4].piece->setPos(6 * 30, 3 * 30);
    boardFields[5].piece->setPos(10 * 30, 3 * 30);

    boardFields[6].piece->setPos(4 * 30, 5 * 30);
    boardFields[7].piece->setPos(6 * 30, 5 * 30);
    boardFields[8].piece->setPos(8 * 30, 5 * 30);


    boardFields[9].piece->setPos(0, 7 * 30);
    boardFields[10].piece->setPos(2 * 30, 7 * 30);
    boardFields[11].piece->setPos(4 * 30, 7 * 30);
    boardFields[12].piece->setPos(8 * 30, 7 * 30);
    boardFields[13].piece->setPos(10 * 30, 7 * 30);
    boardFields[14].piece->setPos(12 * 30, 7 * 30);

    boardFields[15].piece->setPos(4 * 30, 9 * 30);
    boardFields[16].piece->setPos(6 * 30, 9 * 30);
    boardFields[17].piece->setPos(8 * 30, 9 * 30);

    boardFields[18].piece->setPos(2 * 30, 11 * 30);
    boardFields[19].piece->setPos(6 * 30, 11 * 30);
    boardFields[20].piece->setPos(10 * 30, 11 * 30);

    boardFields[21].piece->setPos(0, 13 * 30);
    boardFields[22].piece->setPos(6 * 30, 13 * 30);
    boardFields[23].piece->setPos(12 * 30, 13 * 30);
}

void GameMap::printFieldTerminal(int index, bool lettersOnly) {
    if (lettersOnly) {
        printf("%c", 97 + index);
        return;
    }
    if (boardFields[index].getPlayerID() == FIELDSTATE::PLAYER_1) {
        printf("\033[0;31m");
        printf("0");
        printf("\033[0m");
        return;
    }
    if (boardFields[index].getPlayerID() == FIELDSTATE::PLAYER_2) {
        printf("\033[0;32m");
        printf("0");
        printf("\033[0m");
        return;
    }
    printf("0");
}

void GameMap::printMapTerminal() {
    /* a - - - - - - b - - - - - - c
    *  |             |             |
    *  |             |             |
    *  |     d - - - e - - - f     |
    *  |     |       |       |     |
    *  |     |   g - h - i   |     |
    *  |     |   |       |   |     |
    *  j - - k - l       m - n - - o
    *  |     |   |       |   |     |
    *  |     |   p - q - r   |     |
    *  |     |       |       |     |
    *  |     s - - - t - - - u     |
    *  |             |             |
    *  |             |             |
    *  v - - - - - - w - - - - - - x*/

    printFieldTerminal(0, false);
    printf(" - - - - - - ");
    printFieldTerminal(1, false);
    printf(" - - - - - - ");
    printFieldTerminal(2, false);
    printf("          ");
    printFieldTerminal(0, true);
    printf(" - - - - - - ");
    printFieldTerminal(1, true);
    printf(" - - - - - - ");
    printFieldTerminal(2, true);
    printf("\n");

    printf("|             |             |");
    printf("          ");
    printf("|             |             |");
    printf("\n");
    printf("|             |             |");
    printf("          ");
    printf("|             |             |");
    printf("\n");

    printf("|     ");
    printFieldTerminal(3, false);
    printf(" - - - ");
    printFieldTerminal(4, false);
    printf(" - - - ");
    printFieldTerminal(5, false);
    printf("     |");
    printf("          ");
    printf("|     ");
    printFieldTerminal(3, true);
    printf(" - - - ");
    printFieldTerminal(4, true);
    printf(" - - - ");
    printFieldTerminal(5, true);
    printf("     |");
    printf("\n");

    printf("|     |       |       |     |");
    printf("          ");
    printf("|     |       |       |     |");
    printf("\n");

    printf("|     |   ");
    printFieldTerminal(6, false);
    printf(" - ");
    printFieldTerminal(7, false);
    printf(" - ");
    printFieldTerminal(8, false);
    printf("   |     |");
    printf("          ");
    printf("|     |   ");
    printFieldTerminal(6, true);
    printf(" - ");
    printFieldTerminal(7, true);
    printf(" - ");
    printFieldTerminal(8, true);
    printf("   |     |");
    printf("\n");

    printf("|     |   |       |   |     |");
    printf("          ");
    printf("|     |   |       |   |     |");
    printf("\n");

    printFieldTerminal(9, false);
    printf(" - - ");
    printFieldTerminal(10, false);
    printf(" - ");
    printFieldTerminal(11, false);
    printf("       ");
    printFieldTerminal(12, false);
    printf(" - ");
    printFieldTerminal(13, false);
    printf(" - - ");
    printFieldTerminal(14, false);
    printf("          ");
    printFieldTerminal(9, true);
    printf(" - - ");
    printFieldTerminal(10, true);
    printf(" - ");
    printFieldTerminal(11, true);
    printf("       ");
    printFieldTerminal(12, true);
    printf(" - ");
    printFieldTerminal(13, true);
    printf(" - - ");
    printFieldTerminal(14, true);

    printf("\n");

    printf("|     |   |       |   |     |");
    printf("          ");
    printf("|     |   |       |   |     |");
    printf("\n");

    printf("|     |   ");
    printFieldTerminal(15, false);
    printf(" - ");
    printFieldTerminal(16, false);
    printf(" - ");
    printFieldTerminal(17, false);
    printf("   |     |");
    printf("          ");
    printf("|     |   ");
    printFieldTerminal(15, true);
    printf(" - ");
    printFieldTerminal(16, true);
    printf(" - ");
    printFieldTerminal(17, true);
    printf("   |     |");
    printf("\n");

    printf("|     |       |       |     |");
    printf("          ");
    printf("|     |       |       |     |");
    printf("\n");

    printf("|     ");
    printFieldTerminal(18, false);
    printf(" - - - ");
    printFieldTerminal(19, false);
    printf(" - - - ");
    printFieldTerminal(20, false);
    printf("     |");
    printf("          ");
    printf("|     ");
    printFieldTerminal(18, true);
    printf(" - - - ");
    printFieldTerminal(19, true);
    printf(" - - - ");
    printFieldTerminal(20, true);
    printf("     |");
    printf("\n");

    printf("|             |             |");
    printf("          ");
    printf("|             |             |");
    printf("\n");
    printf("|             |             |");
    printf("          ");
    printf("|             |             |");
    printf("\n");

    printFieldTerminal(21, false);
    printf(" - - - - - - ");
    printFieldTerminal(22, false);
    printf(" - - - - - - ");
    printFieldTerminal(23, false);
    printf("          ");
    printFieldTerminal(21, true);
    printf(" - - - - - - ");
    printFieldTerminal(22, true);
    printf(" - - - - - - ");
    printFieldTerminal(23, true);
    printf("\n");
}

void GameMap::initilizeMills(){
    for(auto &field : boardFields){
        switch (field.getFieldPosition()) {
            case 0:
                field.addMills(1, 2, 9, 21);
                break;
            case 1:
                field.addMills(0, 2, 4, 7);
                break;
            case 2:
                field.addMills(0, 1, 14, 23);
                break;
            case 3:
                field.addMills(4, 5, 10, 18);
                break;
            case 4:
                field.addMills(3, 5, 1, 7);
                break;
            case 5:
                field.addMills(3, 4, 13, 20);
                break;
            case 6:
                field.addMills(7, 8, 11, 15);
                break;
            case 7:
                field.addMills(6, 8, 1, 4);
                break;
            case 8:
                field.addMills(6, 7, 12, 17);
                break;
            case 9:
                field.addMills(0, 21, 10, 11);
                break;
            case 10:
                field.addMills(3, 18, 9, 11);
                break;
            case 11:
                field.addMills(6, 15, 9, 10);
                break;
            case 12:
                field.addMills(8, 17, 13, 14);
                break;
            case 13:
                field.addMills(5, 20, 12, 14);
                break;
            case 14:
                field.addMills(2, 23, 12, 13);
                break;
            case 15:
                field.addMills(6, 11, 16, 17);
                break;
            case 16:
                field.addMills(15, 17, 19, 22);
                break;
            case 17:
                field.addMills(8, 12, 15, 16);
                break;
            case 18:
                field.addMills(3, 10, 19, 20);
                break;
            case 19:
                field.addMills(16, 22, 18, 20);
                break;
            case 20:
                field.addMills(5, 13, 18, 19);
                break;
            case 21:
                field.addMills(0, 9, 22, 23);
                break;
            case 22:
                field.addMills(16, 19, 21, 23);
                break;
            case 23:
                field.addMills(2, 14, 21, 22);
                break;
        }
    }
}


/* vraca indeks polja u nizu
na osnovu pozicije kvadrata
za sada je hardkodovano, kada osmislimo bolje resenje za pozicije
prenece se ovde*/
int GameMap::indexByPos(QPointF position) {
    if (position.rx() == 0 && position.ry() == 30)
        return 0;
    if (position.rx() == 180 && position.ry() == 30)
        return 1;
    if (position.rx() == 360 && position.ry() == 30)
        return 2;

    if (position.rx() == 60 && position.ry() == 90)
        return 3;
    if (position.rx() == 180 && position.ry() == 90)
        return 4;
    if (position.rx() == 300 && position.ry() == 90)
        return 5;

    if (position.rx() == 120 && position.ry() == 150)
        return 6;
    if (position.rx() == 180 && position.ry() == 150)
        return 7;
    if (position.rx() == 240 && position.ry() == 150)
        return 8;

    if (position.rx() == 0 && position.ry() == 210)
        return 9;
    if (position.rx() == 60 && position.ry() == 210)
        return 10;
    if (position.rx() == 120 && position.ry() == 210)
        return 11;
    if (position.rx() == 240 && position.ry() == 210)
        return 12;
    if (position.rx() == 300 && position.ry() == 210)
        return 13;
    if (position.rx() == 360 && position.ry() == 210)
        return 14;

    if (position.rx() == 120 && position.ry() == 270)
        return 15;
    if (position.rx() == 180 && position.ry() == 270)
        return 16;
    if (position.rx() == 240 && position.ry() == 270)
        return 17;

    if (position.rx() == 60 && position.ry() == 330)
        return 18;
    if (position.rx() == 180 && position.ry() == 330)
        return 19;
    if (position.rx() == 300 && position.ry() == 330)
        return 20;

    if (position.rx() == 0 && position.ry() == 390)
        return 21;
    if (position.rx() == 180 && position.ry() == 390)
        return 22;
    if (position.rx() == 360 && position.ry() == 390)
        return 23;

    return -1;
}
