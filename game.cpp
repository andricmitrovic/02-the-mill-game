#include "game.h"
#include "gamemap.h"
#include "player.h"
#include "QGraphicsScene"

Game::Game(Player *p1, Player *p2):
    gameMap(new GameMap()), m_p1(p1), m_p2(p2), gameState(GAMESTATE::INIT),
    winner(FIELDSTATE::EMPTY), millOccured(false), moveFrom(-1), boardPieces(2*NUM_OF_PIECES)
{

  if (gameState != GAMESTATE::INIT)
  {
      setMessage("The game has already been initialized");
      return;
  }

  m_p1->changeTurn(); //prvi je na potezu igrac 1
}



Game::~Game() {
    delete gameMap;
}


bool Game::checkMills(unsigned index) const {
    FIELDSTATE curPlayer = gameMap -> getBoardFields()[index].getPlayerID();
    unsigned checkIndex1 = gameMap -> getBoardFields()[index].getMills().first.first;
    unsigned checkIndex2 = gameMap -> getBoardFields()[index].getMills().first.second;
    if (gameMap -> getBoardFields()[checkIndex1].getPlayerID() == curPlayer &&
        gameMap -> getBoardFields()[checkIndex2].getPlayerID() == curPlayer) {
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
bool Game::makeSetupMove(Player* player, unsigned i, MyGraphicsScene *scene) {
    setMessage("We are in makeSetupMove");

    if (!isValidIndex(i) || gameMap -> getBoardFields()[i].isOccupied()) {
        setMessage("Error: Invalid index or occupied field.");
        return false;
    } else {
        gameMap -> getBoardFields()[i].occupy(player->id());
        boardPieces--;
        player->incNumOfPieces();
        if(player->id() == FIELDSTATE::PLAYER_1 ){
            scene->decrementBluePieces();
            scene->removeItem(gameMap -> getBluePieces()[scene->getBluePieces()]);
        }
        if(player->id() == FIELDSTATE::PLAYER_2 ){
            scene->decrementRedPieces();
            scene->removeItem(gameMap -> getRedPieces()[scene->getRedPieces()]);
        }

        //std::cout << player->getName() << " occupied field " << input << std::endl;
        setMessage(player->getName().toStdString() + " occupied a field.");

        //gameMap -> printMapTerminal();

        if (checkMills(i))
            millOccured = true;
        return true;
    }

}

bool Game::makePlayMove(Player* player, unsigned moveFrom, unsigned moveTo) {
    //setMessage(player->getName() + "'s turn: Choose a piece to move!");

    if (isValidToMove(moveFrom, moveTo)){
        gameMap -> getBoardFields()[moveFrom].deoccupy();
        gameMap -> getBoardFields()[moveTo].occupy(player->id() == FIELDSTATE::PLAYER_1 ? FIELDSTATE::PLAYER_1 : FIELDSTATE::PLAYER_2);

        if (checkMills(moveTo))
            millOccured = true;
        return true;
    }
    return false;

}

/*
    Izmenjeno ponavljanje koda u while petlji
*/

bool Game::removeOpponentsPiece(Player* player, unsigned index) {

    if (!isValidToRemove(index, player))
    {
        setMessage("You can't remove this piece!" );
        return false;
    }
    gameMap -> getBoardFields()[index].deoccupy();

    player->id() == FIELDSTATE::PLAYER_1 ? m_p2->decNumOfPieces() : m_p1->decNumOfPieces();

    millOccured = false;

    Player* opponent = player->id() == FIELDSTATE::PLAYER_1 ? m_p2 : m_p1;
    setMessage("Player " + opponent->getName().toStdString() + " has lost a piece!");
    return true;
}
/*
    Implementacija metoda koji proverava da li je igra zavrsena
    Igra nije gotova sve dok jedan od igraca ne ostane sa dve figurice
*/

bool Game::gameOver() {
    if (m_p1->getNumOfPieces() == 2) {
        setWinner(FIELDSTATE::PLAYER_2);
        return true;
    } else if (m_p2->getNumOfPieces() == 2) {
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
bool Game::isValidToRemove(int i, Player* player) {

    if (!isValidIndex(i)) {
        //std::cout << "Error in index!" << std::endl;
        setMessage("Invalid index");
        return false;
    }
    if (gameMap -> getBoardFields()[i].isOccupied() && gameMap -> getBoardFields()[i].getPlayerID() != player->id()) {

        int numOfPieces = player->id() == FIELDSTATE::PLAYER_1 ? m_p2->getNumOfPieces() : m_p1->getNumOfPieces();

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

bool Game::isValidToSelect(int i, Player* player) const {
    return isValidIndex(i) && gameMap -> getBoardFields()[i].isOccupied() && gameMap -> getBoardFields()[i].getPlayerID() == player->id();
}

void Game::changeTurn() {
    m_p1->changeTurn();
    m_p2->changeTurn();
}

void Game::playMove(Player* player, int index, MyGraphicsScene *scene)
{
    if (this->millOccured){
          //std::cout<< "Mill in playGame"<<std::endl;
          setMessage("Mill in playGame");
          if (removeOpponentsPiece(player, index))
                this->changeTurn();
          return ;
    }

    if (!checkPhase1End()){
            if (makeSetupMove(player, index, scene)){
                if (checkMills(index))
                    millOccured = true;
                else
                    this->changeTurn();
            }
    }else if (!gameOver()){
        if (moveFrom == -1){
            if (isValidToSelect(index, player))
                moveFrom = index;
        }else{ // moveFrom != -1
            if (makePlayMove(player, moveFrom, index)){
                moveFrom = -1;
                if (checkMills(index))
                    millOccured = true;
                else
                    this->changeTurn();

            }else{
                if (gameMap->getBoardFields()[index].getPlayerID() == player->id()){
                    moveFrom = index;

                }
            }

        }
    }else {
        setMessage("Game over!");
        setWinner(m_p1->getNumOfPieces()<m_p2->getNumOfPieces()? FIELDSTATE::PLAYER_2: FIELDSTATE::PLAYER_1);
        std::cout << "GAME OVER" << std:: endl;
    }
}

Player*Game::getCurrentPlayer(){
    return m_p1->turn()? m_p1 : m_p2;
}

GameMap *Game::getGameMap() const
{
    return this -> gameMap;
}

Player* Game::getPlayer1() const
{
    return this -> m_p1;
}

Player* Game::getPlayer2() const
{
    return this -> m_p2;
}

GAMESTATE Game::getGameState()
{
    return this -> gameState;
}

bool Game::getMillOccured()
{
    return this -> millOccured;
}

int Game::getMoveFrom()
{
    return this -> moveFrom;
}

int Game::getBoardPieces()
{
    return this -> boardPieces;
}

// Proverava da li su sve figurice postavljene i ako jesu zavrsava phase1
bool Game::checkPhase1End() {
    if (boardPieces == 0) {
        //std::cout << "The game has been set up!" << std::endl;
        setMessage("The game has been set up!");
        //std::cout << "Player 1 No. of pieces: " << m_p1->getNumOfPieces() << std::endl;
        //std::cout << "Player 2 No. of pieces: " << m_p2->getNumOfPieces() << std::endl;

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

void Game::setGameMap(GameMap *gameMap)
{
    this -> gameMap = gameMap;
}

void Game::setPlayer1(Player* p1)
{
    this -> m_p1 = p1;
}

void Game::setPlayer2(Player* p2)
{
    this -> m_p2 = p2;
}

void Game::setGameState(GAMESTATE gameState)
{
    this -> gameState = gameState;
}

void Game::setMillOccured(bool millOccured)
{
    this -> millOccured = millOccured;
}

void Game::setMoveFrom(int moveFrom)
{
    this -> moveFrom = moveFrom;
}

void Game::setBoardPieces(int boardPieces)
{
    this -> boardPieces = boardPieces;
}
