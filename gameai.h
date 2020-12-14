#ifndef GAMEAI_H
#define GAMEAI_H

#include "gamemap.h"
#include "player.h"
#include "lib.h"

/*
 * Klasa Game
 * sadrzi GameMap (mapa koju je Marija pravila koja sadrzi vektor svih polja)
 *        dva igraca (za sada su oba Player)
 */

class GameAI {
public:

    GameAI(Player& p1, Player& p2);
    ~GameAI();

    // metode
    void play(); // ovo je igranje igre, odnosno premestanje vec postavljenih figura
    void setup(); // ovo je postavljanje figura, tj. prva faza igre
    void setup_graphical();

    void changeTurn();
    bool makePlayMove(Player& player);
    bool makeSetupMove(Player& player);
    void playMove(Player& player, int index, QGraphicsScene &scene);
    void removeOpponentsPiece(Player& player);

    bool makeSetupMove_graphical(Player &player, unsigned i, QGraphicsScene &scene);
    bool removeOpponentsPiece_graphic(Player& player, unsigned index);
    bool makePlayMove_graphical(Player &player, unsigned moveFrom, unsigned moveTo);

    // metodi za proveru stanje igre
    bool gameOver();
    bool checkPhase1End();
    bool checkMills(unsigned index) const;

    //provera indeks

    bool isValidIndex(int i) const;
    bool isValidToMove(int from, int to) const;
    bool isValidToRemove(int i, Player& player);
    bool isValidToSelect(int i, Player& player) const;
    bool isValidToOccupy(int i, Player& player) const;

    // ovde dodajem AI funkcije
    void makeSetupMove_AI(Player & player, int i);    // ides u drugu klasu
    void revertSetupMove_AI(Player & player, int i);

    // getteri
    QString getMessage() const;
    FIELDSTATE getWinner() const;
    Player &getCurrentPlayer();

    // setteri
    void setWinner(FIELDSTATE winner);
    void setMessage(const std::string &msg);

    //ai funkcije
    std::pair<int,int> max(int depth);
    std::pair<int,int> min(int depth);

    // seteri i geteri za ovo sve
    GameMap         *gameMap;               // i ovo mi treba public
    Player          m_p1;                   // stavio sam public jer mi treba turn metoda nad ovim objektima
    Player          m_p2;                   // public
    int             phase1_piece_counter;   // dodao ovo ovde da bi iz boarda znao kada da prekinem prvi deo igre
    GAMESTATE       gameState;
    bool            mill_occured;
    int             moveFrom;
    int             boardPieces;

    int             maxDepthAI;

private:
    FIELDSTATE      winner;
    QString         message;


};

#endif // GAMEAI_H
