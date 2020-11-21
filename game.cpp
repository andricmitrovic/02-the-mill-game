#include "game.h"

#include "humanplayer.h"
#include "gamemap.h"


#include <iostream>

#define NUM_OF_PIECES (9) //broj figura po igracu

Game::Game()
    : gameMap(new GameMap()),
      m_p1(HumanPlayer(VALUE::PLAYER_1)),
      m_p2(HumanPlayer(VALUE::PLAYER_2))
{
}

void Game::setup(){
    m_p1.changeTurn(); //prvi je na potezu igrac 1

    unsigned i;
    while (gameMap->numofpieces2 < NUM_OF_PIECES){
        if (m_p1.turn()){
            std::cout << "Player 1 turn: Choose a field [0-23]" << std::endl;
            std::cin >> i;
            if (gameMap->boardFields[i].isOccupied() || i > 23){
                std::cout << "Invalid move! Try again..." << std::endl;
            }
            else{
                gameMap->boardFields[i].occupy(m_p1.id());
                gameMap->numofpieces1++;
                std::cout << "Player 1 occupied field " << i << std::endl;
                m_p1.changeTurn();
                m_p2.changeTurn();
            }

        }
        else if (m_p2.turn()){
            std::cout << "Player 2 turn: Choose a field [0-23]" << std::endl;
            std::cin >> i;
            if (gameMap->boardFields[i].isOccupied() || i > 23){
                std::cout << "Invalid move! Try again..." << std::endl;
            }
            else{
                gameMap->boardFields[i].occupy(m_p2.id());
                gameMap->numofpieces2++;
                std::cout << "Player 2 occupied field " << i << std::endl;
                m_p2.changeTurn();
                m_p1.changeTurn();
            }
        }

    } //end while
    std::cout << "The game has been set up!" << std::endl;
    std::cout << "Player 1 No. of pieces: " << gameMap->numofpieces1 << std::endl;
    std::cout << "Player 2 No. of pieces: " << gameMap->numofpieces2 << std::endl;


}
