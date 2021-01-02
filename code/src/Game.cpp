#include "code/include/Game.h"
#include "code/include/Player.h"
#include "code/include/GameMap.h"
#include "code/include/MyGraphicsScene.h"


Game::Game(Player *p1, Player *p2):
    gameMap(new GameMap()), m_p1(p1), m_p2(p2), gameState(GAMESTATE::INIT),
    winner(FIELDSTATE::EMPTY), millOccured(false), moveFrom(-1), boardPieces(2*NUM_OF_PIECES)
{

  if (gameState != GAMESTATE::INIT)
  {
      setGameMessage("The game has already been initialized");
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

bool Game::hasAvailableFields(Player *player) const {
    for (auto field : gameMap->getBoardFields()) {
        if (field.getPlayerID() == player->id()) {
            for (auto neighbourIndex : field.getNeighboursIndices()) {
                if (!gameMap->getBoardFields().at(neighbourIndex).isOccupied())
                    return true;
            }
        }
    }
    return false;
}


// Postavlja figuricu na polje i, koje smo dobili iz klika
bool Game::makeSetupMove(Player* player, unsigned i, MyGraphicsScene *scene) {
    if (!isValidIndex(i) || gameMap -> getBoardFields()[i].isOccupied()) {
        setErrorMessage("Error: Invalid index or occupied field.");
        return false;
    } else {
        Player* opponent = player->id() == FIELDSTATE::PLAYER_1 ? m_p2 : m_p1;
        setGameMessage(opponent->getName().toStdString() + "'s turn. Choose a field to place your piece.");
        gameMap -> getBoardFields()[i].occupy(player->id());
        boardPieces--;
        if (boardPieces == 0) {
            setGameMessage("The game has been set up! Move your pieces around");
        }
        player->incNumOfPieces();
        if(player->id() == FIELDSTATE::PLAYER_1 ){
            scene->decrementBluePieces();
            scene->removeItem(gameMap -> getBluePieces()[scene->getBluePieces()]);
        }
        if(player->id() == FIELDSTATE::PLAYER_2 ){
            scene->decrementRedPieces();
            scene->removeItem(gameMap -> getRedPieces()[scene->getRedPieces()]);
        }

        if (checkMills(i))
            millOccured = true;
        return true;
    }

}

bool Game::makePlayMove(Player* player, unsigned moveFrom, unsigned moveTo) {
    if (isValidToMove(moveFrom, moveTo)){
        Player* opponent = player->id() == FIELDSTATE::PLAYER_1 ? m_p2 : m_p1;
        setGameMessage(opponent->getName().toStdString() + "'s turn");
        gameMap -> getBoardFields()[moveFrom].deoccupy();
        gameMap -> getBoardFields()[moveTo].occupy(player->id() == FIELDSTATE::PLAYER_1 ? FIELDSTATE::PLAYER_1 : FIELDSTATE::PLAYER_2);

        if (checkMills(moveTo)) {
            millOccured = true;
            setGameMessage("-- MILL -- Choose an opponent's piece to remove!");
        }
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
        setErrorMessage("You can't remove this piece!" );
        return false;
    }
    gameMap -> getBoardFields()[index].deoccupy();

    player->id() == FIELDSTATE::PLAYER_1 ? m_p2->decNumOfPieces() : m_p1->decNumOfPieces();

    millOccured = false;

    Player* opponent = player->id() == FIELDSTATE::PLAYER_1 ? m_p2 : m_p1;
    setGameMessage(opponent->getName().toStdString() + " has lost a piece!\n" + opponent->getName().toStdString() + "'s turn");
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
    } else if (!hasAvailableFields(m_p1)) {
        setWinner(FIELDSTATE::PLAYER_2);
        return true;
    } else if (!hasAvailableFields(m_p2)) {
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
bool Game::isValidToRemove(int i, Player* player, bool displayError) {

    if (!isValidIndex(i)) {
        setErrorMessage("Invalid index");
        return false;
    }
    if (gameMap -> getBoardFields()[i].isOccupied() && gameMap -> getBoardFields()[i].getPlayerID() != player->id()) {

        int numOfPieces = player->id() == FIELDSTATE::PLAYER_1 ? m_p2->getNumOfPieces() : m_p1->getNumOfPieces();

        FIELDSTATE player_2 = player->id() == FIELDSTATE::PLAYER_1 ? FIELDSTATE::PLAYER_2 : FIELDSTATE::PLAYER_1;
        if (!checkMills(i) || numOfPieces == 3) {
            return true;
        } else if(numOfPieces >3){
            for (auto &field:gameMap->getBoardFields()){
                if (field.getPlayerID() == player_2 && !checkMills(field.getFieldPosition())){
                    if(displayError)
                        setErrorMessage("You can't remove piece from the mill just yet!");
                    return false;
                }
            }
            return true;
        }else{
            if(displayError)
                setErrorMessage("You can't remove piece from the mill just yet!");
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
          if (removeOpponentsPiece(player, index))
                this->changeTurn();
          return;
    }

    if (!checkPhase1End()){
            if (makeSetupMove(player, index, scene)){
                if (checkMills(index)) {
                    millOccured = true;
                    setGameMessage("-- MILL -- Choose an opponent's piece to remove!");
                }
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
        setWinner(m_p1->getNumOfPieces()<m_p2->getNumOfPieces()? FIELDSTATE::PLAYER_2: FIELDSTATE::PLAYER_1);
        if (winner == FIELDSTATE::PLAYER_1)
            setGameMessage("Game over! Player 1 won!");
        else
            setGameMessage("Game over! Player 2 won");
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
        gameState = GAMESTATE::PLAY;
        return true;
    }
    return false;
}

QString Game::getGameMessage() const {
    return gameMessage;
}

QString Game::getErrorMessage() const {
    return errorMessage;
}

void Game::setGameMessage(const std::string & msg){
    gameMessage = gameMessage.fromStdString(msg);
}

void Game::clearGameMessage() {
    gameMessage.clear();
}

void Game::clearErrorMessage() {
    errorMessage.clear();
}

void Game::setErrorMessage(const std::string &msg) {
    errorMessage = errorMessage.fromStdString(msg);
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
