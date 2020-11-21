#include "game.h"

#include "humanplayer.h"
#include "gamemap.h"


#include <iostream>

#define NUM_OF_PIECES (9) //broj figura po igracu

Game::Game()
    : gameMap(new GameMap()),
      m_p1(HumanPlayer(VALUE::PLAYER_1)),
      m_p2(HumanPlayer(VALUE::PLAYER_2)),
      gameState(GAMESTATE::INIT)
{
}

bool Game::checkMills(unsigned index){
    VALUE curPlayer = gameMap->boardFields[index].getPlayerID();
    unsigned checkIndex1 = gameMap->boardFields[index].getMills().first.first;
    unsigned checkIndex2 = gameMap->boardFields[index].getMills().first.second;
    if(gameMap->boardFields[checkIndex1].getPlayerID() == curPlayer && gameMap->boardFields[checkIndex2].getPlayerID() == curPlayer){
        return true;
    }

    unsigned checkIndex3 = gameMap->boardFields[index].getMills().second.first;
    unsigned checkIndex4 = gameMap->boardFields[index].getMills().second.second;
    if(gameMap->boardFields[checkIndex3].getPlayerID() == curPlayer && gameMap->boardFields[checkIndex4].getPlayerID() == curPlayer){
        return true;
    }
    return false;
}

void Game::removeOpponentsPiece(){
    std::cout << "MILL!" << std::endl;
    int i;
    char input;
    while(true){
        if(m_p1.turn()){
            std::cout <<"Player 1 turn: Choose an oppnents piece to remove [a-x]" << std::endl;
            std::cin >> input;
            i = input - 97;
            if(i >= 0 && i <= 23 && gameMap->boardFields[i].isOccupied() && gameMap->boardFields[i].getPlayerID() == VALUE::PLAYER_2){
                gameMap->boardFields[i].deoccupy();
                std::cout << "Player 2 has lost one piece at the field " << input << std::endl;
                gameMap->printMapTerminal();
                break;
            } else {
                std::cout << "Invalid choice! Try again..." << std::endl;
            }
        } else if(m_p2.turn()){
            std::cout << "Player 2 turn: Choose an oppnents piece to remove [a-x]" << std::endl;
            std::cin >> input;
            i = input - 97;
            if(i >= 0 && i <= 23 && gameMap->boardFields[i].isOccupied() && gameMap->boardFields[i].getPlayerID() == VALUE::PLAYER_1){
                gameMap->boardFields[i].deoccupy();
                std::cout << "Player 1 has lost one piece at the field " << input << std::endl;
                gameMap->printMapTerminal();
                break;
            } else {
                std::cout << "Invalid choice! Try again..." << std::endl;
            }
        }
    }
}

void Game::setup(){
    if(gameState != GAMESTATE::INIT){
        std::cout << "The has already been initialized" << std::endl;
        return;
    }

    m_p1.changeTurn(); //prvi je na potezu igrac 1
    gameMap->printMapTerminal();

    int i;
    char input;
    while (gameMap->numofpieces2 < NUM_OF_PIECES){
        if (m_p1.turn()){
            std::cout << "Player 1 turn: Choose a field [a-x]" << std::endl;
            std::cin >> input;
            i = input - 97;
            if(i < 0 || i >23 || gameMap->boardFields[i].isOccupied()){
                std::cout << "Invalid move! Try again..." << std::endl;
            }
            else{
                gameMap->boardFields[i].occupy(m_p1.id());
                gameMap->numofpieces1++;
                std::cout << "Player 1 occupied field " << input << std::endl;
                gameMap->printMapTerminal();
                if(checkMills(i)){
                    removeOpponentsPiece();
                }
                m_p1.changeTurn();
                m_p2.changeTurn();
            }

        }
        else if (m_p2.turn()){
            std::cout << "Player 2 turn: Choose a field [a-x]" << std::endl;
            std::cin >> input;
            i = input - 97;
            if(i < 0 || i >23 || gameMap->boardFields[i].isOccupied()){
                std::cout << "Invalid move! Try again..." << std::endl;
            }
            else{
                gameMap->boardFields[i].occupy(m_p2.id());
                gameMap->numofpieces2++;
                std::cout << "Player 2 occupied field " << i << std::endl;
                gameMap->printMapTerminal();
                if(checkMills(i)){
                    removeOpponentsPiece();
                }
                m_p2.changeTurn();
                m_p1.changeTurn();
            }
        }

    } //end while
    std::cout << "The game has been set up!" << std::endl;
    std::cout << "Player 1 No. of pieces: " << gameMap->numofpieces1 << std::endl;
    std::cout << "Player 2 No. of pieces: " << gameMap->numofpieces2 << std::endl;

    gameMap->printMapTerminal();
    gameState = GAMESTATE::PLAY;
}

void Game::play(){
    if(gameState != GAMESTATE::PLAY){
        std::cout << "The game is not initialized" << std::endl;
        return;
    }
}
