#include "game.h"
#include "gamemap.h"
#include "humanplayer.h"
#include "QGraphicsScene"

Game::Game(HumanPlayer & p1, HumanPlayer & p2)
    : gameMap(new GameMap()), m_p1(p1), m_p2(p2), gameState(GAMESTATE::INIT),
      mill_occured(false), moveFrom(-1), boardPieces(2*NUM_OF_PIECES), winner(FIELDSTATE::EMPTY){}

Game::~Game() {
    delete gameMap;
}

bool Game::checkMills(unsigned index) const {
    FIELDSTATE curPlayer = gameMap -> getBoardFields()[index].getPlayerID();
    unsigned checkIndex1 = gameMap -> getBoardFields()[index].getMills().first.first;
    unsigned checkIndex2 = gameMap -> getBoardFields()[index].getMills().first.second;
    if (gameMap -> getBoardFields()[checkIndex1].getPlayerID() == curPlayer && gameMap -> getBoardFields()[checkIndex2].getPlayerID() == curPlayer) {
        return true;
    }

    unsigned checkIndex3 = gameMap -> getBoardFields()[index].getMills().second.first;
    unsigned checkIndex4 = gameMap -> getBoardFields()[index].getMills().second.second;
    if (gameMap -> getBoardFields()[checkIndex3].getPlayerID() == curPlayer && gameMap -> getBoardFields()[checkIndex4].getPlayerID() == curPlayer) {
        return true;
    }
    return false;
}


// Postavlja figuricu na polje i, koje smo dobili iz klika
bool Game::makeSetupMove_graphical(HumanPlayer & player, unsigned i, QGraphicsScene &scene) {

    //std::cout << player.getName() << "'s turn:  Choose a field [a-x]: " << std::endl;
    //setMessage(player.getName() + "'s turn:  Choose a field [a-x]: ");
    setMessage("We are in makeSetupMove_graphical");
    if (!isValidIndex(i) || gameMap -> getBoardFields()[i].isOccupied()) {
        std::cout << "Error: Invalid index or occupied field." << std::endl;
        setMessage("Error: Invalid index or occupied field.");
        return false;
    } else {
        gameMap -> getBoardFields()[i].occupy(player.id());
        boardPieces--;
        player.incNumOfPieces();
        scene.removeItem(gameMap -> getPieces()[gameMap -> getRemoveIndex()]);
        gameMap -> incRemoveIndex();

        //std::cout << player.getName() << " occupied field " << input << std::endl;
        //setMessage(player.getName() + " occupied a field.");

        //gameMap -> printMapTerminal();

        if (checkMills(i))
            mill_occured = true;
        return true;
    }

}


bool Game::makePlayMove_graphical(HumanPlayer & player, unsigned moveFrom, unsigned moveTo) {
    //setMessage(player.getName() + "'s turn: Choose a piece to move!");

    if (isValidToMove(moveFrom, moveTo)){
        gameMap -> getBoardFields()[moveFrom].deoccupy();
        gameMap -> getBoardFields()[moveTo].occupy(player.id() == FIELDSTATE::PLAYER_1 ? FIELDSTATE::PLAYER_1 : FIELDSTATE::PLAYER_2);

        if (checkMills(moveTo))
            mill_occured = true;
        return true;
    }
    return false;

}

/*
    Izmenjeno ponavljanje koda u while petlji
*/

bool Game::removeOpponentsPiece_graphic(HumanPlayer & player, unsigned index) {

    if (!isValidToRemove(index, player))
    {
        setMessage("You can't remove this piece!" );
        return false;
    }
    gameMap -> getBoardFields()[index].deoccupy();

    player.id() == FIELDSTATE::PLAYER_1 ? m_p2.decNumOfPieces() : m_p1.decNumOfPieces(); // ????? Da ne treba mozda ovde obrnuto

    mill_occured = false;

    //setMessage("Player " + player.getName() + " has lost a piece!");
    return true;
}
/*
    Implementacija metoda koji proverava da li je igra zavrsena
    Igra nije gotova sve dok jedan od igraca ne ostane sa dve figurice
*/

bool Game::gameOver() {
    if (m_p1.getNumOfPieces() == 2) {
        setWinner(FIELDSTATE::PLAYER_2);
        return true;
    } else if (m_p2.getNumOfPieces() == 2) {
        setWinner(FIELDSTATE::PLAYER_1);
        return true;
    }
    return false;
}

/*
    setter za winnera
*/
void Game::setWinner(FIELDSTATE winner) {
    this -> winner = winner;
}


FIELDSTATE Game::getWinner() const {
    return winner;
}

bool Game::isValidIndex(int i) const {
    return (i >= 0 && i < NUM_OF_FIELDS);
}

/*
 *  Implementacija meotde isValidToRemove: provera da li player sme da ukloni figuru sa polja i
 *  Metoda se poziva kada player napravil Mill
 *
 */
bool Game::isValidToRemove(int i, HumanPlayer & player) {

    if (!isValidIndex(i)) {
        std::cout << "Error in index!" << std::endl;
        return false;
    }
    if (gameMap -> getBoardFields()[i].isOccupied() && gameMap -> getBoardFields()[i].getPlayerID() != player.id()) {

        int numOfPieces = player.id() == FIELDSTATE::PLAYER_1 ? m_p2.getNumOfPieces() : m_p1.getNumOfPieces();

        if (!checkMills(i) || numOfPieces == 3) {
            return true;
        } else {
            setMessage("You can't remove piece from the mill just yet!");
            return false;
        }

    }
    return false;
}

bool Game::isValidToMove(int from, int to) const {

    if (!isValidIndex(from) || !isValidIndex(to)) {
        return false;
    }

    auto neighbours = gameMap -> getBoardFields()[from].getNeighboursIndices();
    bool contains = (std::find(neighbours.begin(), neighbours.end(), to) != neighbours.end());

    // Ukoliko je izabrano polje prazno i sused je polja i

    return (!gameMap -> getBoardFields()[to].isOccupied() && contains);
}

bool Game::isValidToSelect(int i, HumanPlayer & player) const {
    return isValidIndex(i) && gameMap -> getBoardFields()[i].isOccupied() && gameMap -> getBoardFields()[i].getPlayerID() == player.id();
}

bool Game::isValidToOccupy(int i, HumanPlayer & player) const {
    return false;
}

void Game::changeTurn() {
    m_p1.changeTurn();
    m_p2.changeTurn();
}

void Game::playMove(HumanPlayer &player, int index, QGraphicsScene &scene)
{

    if (this->mill_occured){
          std::cout<< "Mill in playGame"<<std::endl;
          if (removeOpponentsPiece_graphic(player, index))
                this->changeTurn();
          return ;
    }

    if (!checkPhase1End()){
            if (makeSetupMove_graphical(player, index, scene)){
                if (checkMills(index))
                    mill_occured = true;
                else
                    this->changeTurn();
            }
    }else if (!gameOver()){
        if (moveFrom == -1){
            if (isValidToSelect(index, player))
                moveFrom = index;
        }else{ // moveFrom != -1
            if (makePlayMove_graphical(player, moveFrom, index)){
                moveFrom = -1;
                if (checkMills(index))
                    mill_occured = true;
                else
                    this->changeTurn();

            }else{
                if (gameMap->getBoardFields()[index].getPlayerID() == player.id()){
                    moveFrom = index;

                }
            }

        }
    }else {
        setMessage("Game over!");
        setWinner(m_p1.getNumOfPieces()<m_p2.getNumOfPieces()? FIELDSTATE::PLAYER_2: FIELDSTATE::PLAYER_1);
        std::cout << "GAME OVER" << std:: endl;
    }
}

HumanPlayer &Game::getCurrentPlayer(){
    return m_p1.turn()? m_p1 : m_p2;
}


// Inicijalizuje neke gluposti vrv mozemo i bez ovoga, da se stavi u konstruktor npr
void Game::setup_graphical() {
    if (gameState != GAMESTATE::INIT) {
        std::cout << "The has already been initialized" << std::endl;
        setMessage("The game has already been initialized");
        return;
    }

    m_p1.changeTurn(); //prvi je na potezu igrac 1
}

// Proverava da li su sve figurice postavljene i ako jesu zavrsava phase1

bool Game::checkPhase1End() {
    if (boardPieces == 0) {
        //std::cout << "The game has been set up!" << std::endl;
        setMessage("The game has been set up!");
        //std::cout << "Player 1 No. of pieces: " << m_p1.getNumOfPieces() << std::endl;
        //std::cout << "Player 2 No. of pieces: " << m_p2.getNumOfPieces() << std::endl;

        //gameMap -> printMapTerminal();
        gameState = GAMESTATE::PLAY;
        return true;
    }
    return false;
}


QString Game::getMessage() const {
    return message;
}

void Game::setMessage(const std::string & msg){
    message.clear();
    message = message.fromStdString(msg);
}
