#include "gamelocal.h"
#include "gamemap.h"
#include "player.h"
#include "QGraphicsScene"

GameLocal::GameLocal(Player* p1, Player* p2):
    Game(p1, p2)
{

}

/*
GameLocal::~GameLocal() {
    delete gameMap;
}*/


/*
 * void Game::setup() {
    if (gameState != GAMESTATE::INIT) {
        std::cout << "The has already been initialized" << std::endl;
        return;
    }

    m_p1.changeTurn(); //prvi je na potezu igrac 1
    gameMap -> printMapTerminal();

    int i = 0;
    while (i <= 2 * NUM_OF_PIECES) {
        if (m_p1.turn()) {
            while (!makeSetupMove(m_p1));
            changeTurn();
        } else {
            while (!makeSetupMove(m_p2));
            changeTurn();
        }
        i++;

    } //end while
    std::cout << "The game has been set up!" << std::endl;
    std::cout << "Player 1 No. of pieces: " << m_p1.getNumOfPieces() << std::endl;
    std::cout << "Player 2 No. of pieces: " << m_p2.getNumOfPieces() << std::endl;

    gameMap -> printMapTerminal();
    gameState = GAMESTATE::PLAY;

}


void Game::play() {
    if (gameState != GAMESTATE::PLAY) {
        std::cout << "The game is not initialized" << std::endl;
        return;
    }
    std::cout << "PLAY PART" << std::endl;

    while (!gameOver()) {
        if (m_p1.turn()) {
            while (!makePlayMove(m_p1));
            gameMap -> printMapTerminal();
            changeTurn();
        } else {
            while (!makePlayMove(m_p2));
            gameMap -> printMapTerminal();
            changeTurn();
        }
    }

    std::cout << "The game is over" << std::endl;
    if (getWinner() == FIELDSTATE::PLAYER_1) {
        std::cout << "PLAYER 1 is the winner" << std::endl;
    } else if (getWinner() == FIELDSTATE::PLAYER_2) {
        std::cout << "PLAYER 1 is the winner" << std::endl;
    } else {
        std::cout << "Error" << std::endl;
    }

}

void Game::removeOpponentsPiece(Player & player) {
    std::cout << "MILL!" << std::endl;
    int index;
    char input_index;

    while (true) {
        std::cout << player.getName() << "'s turn: Choose an oppnents piece to remove [a-x]:" << std::endl;
        std::cin >> input_index;
        index = input_index - 'a';

        if (isValidToRemove(index, player)) {
            gameMap -> getBoardFields()[index].deoccupy();
            player.id() == FIELDSTATE::PLAYER_1 ? m_p2.decNumOfPieces() : m_p1.decNumOfPieces();
            std::cout << "Player has lost one piece at the field " << input_index << std::endl;
            //gameMap -> printMapTerminal();
            break;
        } else {
            std::cout << "Invalid choice! Try again..." << std::endl;
        }
    }
}

bool Game::makePlayMove(Player & player) {
    char input;
    int i;
    std::cout << player.getName() << "'s turn: Choose a piece to move: [a-x]: " << std::endl;
    std::cin >> input;
    i = input - 'a';

    if (isValidToSelect(i, player)) {
        std::cout << player.getName() << "'s turn: Choose field you want to move to selected piece: [a-x]: " << std::endl;
        std::cin >> input;
        const int j = input - 'a';

        // Ukoliko je izabrano polje prazno i sused je polja i
        if (isValidToMove(i, j)) {
            gameMap -> getBoardFields()[i].deoccupy();
            gameMap -> getBoardFields()[j].occupy(player.id() == FIELDSTATE::PLAYER_1 ? FIELDSTATE::PLAYER_2 : FIELDSTATE::PLAYER_1);
            std::cout << "Piece moved from " << input << " to " << input << std::endl;

            if (checkMills(j))
                removeOpponentsPiece(player);

        } else if (gameMap -> getBoardFields()[j].isOccupied()) {
            std::cout << "Error: field " << input << "is already occupied! Try again!" << std::endl;
            return false;

        } else {
            std::cout << "Error : You can only move piece to neighbour field" << std::endl;
            return false;
        }
        gameMap -> printMapTerminal();

    } else {
        std::cout << "Invalid choice! Try again..." << std::endl;
        return false;
    }
    return true;
}


bool Game::makeSetupMove(Player & player) {
    int i;
    char input;

    std::cout << player.getName() << "'s turn:  Choose a field [a-x]: " << std::endl;

    std::cin >> input;
    i = input - 'a';

    if (!isValidIndex(i) || gameMap -> getBoardFields()[i].isOccupied()) {
        std::cout << "Error: Invalid index or occupied field." << std::endl;
        return false;
    } else {
        gameMap -> getBoardFields()[i].occupy(player.id());
        player.incNumOfPieces();

        std::cout << player.getName() << " occupied field " << input << std::endl;

        gameMap -> printMapTerminal();

        if (checkMills(i))
            removeOpponentsPiece(player);
    }
    return true;
}

*/
