#include "game.h"
#include "gamemap.h"
#include "humanplayer.h"


Game::Game(HumanPlayer &p1, HumanPlayer &p2)
    :gameMap(new GameMap()), m_p1(p1), m_p2(p2), gameState(GAMESTATE::INIT), winner(FIELDSTATE::EMPTY), mill_occured(false)
{}

Game::~Game()
{
    delete gameMap;
}


bool Game::checkMills(unsigned index) const{
    FIELDSTATE curPlayer = gameMap->boardFields[index].getPlayerID();
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



bool Game::makeSetupMove(HumanPlayer &player){
    int i;
    char input;

    std::cout << player.getName() <<"'s turn:  Choose a field [a-x]: " << std::endl;

    std::cin >> input;
    i = input - 'a';

    if(!isValidIndex(i) || gameMap->boardFields[i].isOccupied()) {
        std::cout << "Error: Invalid index or occupied field." << std::endl;
        return false;
    }
    else{
        gameMap->boardFields[i].occupy(player.id());
        player.incNumOfPieces();

        std::cout << player.getName() << " occupied field " << input << std::endl;


        gameMap->printMapTerminal();

        if(checkMills(i))
            removeOpponentsPiece(player);


    }
    return true;
}

// Postavlja figuricu na polje i, koje smo dobili iz klika
bool Game::makeSetupMove_graphical(HumanPlayer &player, unsigned i){

    std::cout << player.getName() <<"'s turn:  Choose a field [a-x]: " << std::endl;
    setMesssage(player.getName() + "'s turn:  Choose a field [a-x]: ");

    if(!isValidIndex(i) || gameMap->boardFields[i].isOccupied()) {
        std::cout << "Error: Invalid index or occupied field." << std::endl;
        setMesssage("Error: Invalid index or occupied field.");
        return false;
    }
    else{
        gameMap->boardFields[i].occupy(player.id());
        phase1_piece_counter--;
        player.incNumOfPieces();

        //std::cout << player.getName() << " occupied field " << input << std::endl;
        setMesssage(player.getName() + " occupied a field." );

        gameMap->printMapTerminal();

        if(checkMills(i))
            mill_occured = true;

    }
    return true;
}

bool Game::makePlayMove(HumanPlayer &player)
{
    char input;
    int i;
    std::cout <<player.getName() <<"'s turn: Choose a piece to move: [a-x]: " << std::endl;
    std::cin >> input;
    i = input - 'a';

    if(isValidToSelect(i, player)){

        std::cout << player.getName()<<"'s turn: Choose field you want to move to selected piece: [a-x]: " << std::endl;
        std::cin >> input;
        const int j = input-'a';

        // Ukoliko je izabrano polje prazno i sused je polja i
        if (isValidToMove(i, j)){
            gameMap->boardFields[i].deoccupy();
            gameMap->boardFields[j].occupy(player.id() == FIELDSTATE::PLAYER_1? FIELDSTATE::PLAYER_2 : FIELDSTATE::PLAYER_1);
            std::cout << "Piece moved from " << input << " to "<< input<< std::endl;

            if (checkMills(j))
                removeOpponentsPiece(player);

        }else if(gameMap->boardFields[j].isOccupied()) {
            std::cout<< "Error: field "<< input << "is already occupied! Try again!"<< std::endl;
            return false;

        }else{
            std::cout<< "Error : You can only move piece to neighbour field"<<std::endl;
            return false;
        }
       gameMap->printMapTerminal();

    } else {
        std::cout << "Invalid choice! Try again..." << std::endl;
        return false;
    }
    return true;
}

bool Game::makePlayMove_graphical(HumanPlayer &player, unsigned moveFrom, unsigned moveTo)
{
    setMesssage(player.getName() + "'s turn: Choose a piece to move!");

    if(isValidToSelect(moveFrom, player)){
        // Ukoliko je izabrano polje prazno i sused je polja i
        if (isValidToMove(moveFrom, moveTo)){
            gameMap->boardFields[moveFrom].deoccupy();
            gameMap->boardFields[moveTo].occupy(player.id() == FIELDSTATE::PLAYER_1 ? FIELDSTATE::PLAYER_1 : FIELDSTATE::PLAYER_2);

            if (checkMills(moveTo))
                removeOpponentsPiece_graphic(player, moveTo);

        } else if(gameMap->boardFields[moveTo].isOccupied()) {
            setMesssage("Error! Field is already occupied. Try again...");
            return false;

        } else{
            setMesssage("You can only move piece to neighbour field ");
            return false;
        }

    } else {
        setMesssage("Invalid choice! Try again...");
        return false;
    }
    return true;
}

/*
    Izmenjeno ponavljanje koda u while petlji
*/

void Game::removeOpponentsPiece(HumanPlayer& player){
    std::cout << "MILL!" << std::endl;
    int index;
    char input_index;

    while(true){
            std::cout <<player.getName()<<"'s turn: Choose an oppnents piece to remove [a-x]:" << std::endl;
            std::cin >> input_index;
            index = input_index - 'a';

            if(isValidToRemove(index, player)){
                gameMap->boardFields[index].deoccupy();
                player.id() == FIELDSTATE::PLAYER_1? m_p2.decNumOfPieces() : m_p1.decNumOfPieces();
                std::cout << "Player has lost one piece at the field " << input_index << std::endl;
                gameMap->printMapTerminal();
                break;
            } else {
                std::cout << "Invalid choice! Try again..." << std::endl;
            }
    }
}

// Popraviti ovu funkciju !!!!!!!!!!!!!!!!!!!!!!!!!
// Kad se desi mill uklanja figuricu igraca na poziciji
void Game::removeOpponentsPiece_graphic(HumanPlayer& player, unsigned index){

    /*if(isValidToRemove(index, player))
    {
                gameMap->boardFields[index].deoccupy();
                player.id() == FIELDSTATE::PLAYER_1? m_p1.decNumOfPieces() : m_p2.decNumOfPieces();     // ????? Da ne treba mozda ovde obrnuto
                gameMap->printMapTerminal();
                mill_occured = false;
                std::cout << "Player has lost one piece" << std::endl;
    }
    else
    {
                    std::cout << "Invalid choice! Try again..." << std::endl;
    }*/

    // !!!!!!!!!!!!!!!!! ne prolazi if gore nz sto !!!!!!!!!!!!!!!!!

    setMesssage("MILL! Choose an opponent's piece to remove");
    gameMap->boardFields[index].deoccupy();
    player.id() == FIELDSTATE::PLAYER_1? m_p2.decNumOfPieces() : m_p1.decNumOfPieces();     // ????? Da ne treba mozda ovde obrnuto
    gameMap->printMapTerminal();
    mill_occured = false;
    std::cout << "Player has lost one piece" << std::endl;
    setMesssage("Player " + player.getName() + " has lost a piece!");

}
/*
    Implementacija metoda koji proverava da li je igra zavrsena
    Igra nije gotova sve dok jedan od igraca ne ostane sa dve figurice
*/

bool Game::gameOver()
{
    if (m_p1.getNumOfPieces() == 2)
    {
        setWinner(FIELDSTATE::PLAYER_2);
        return true;
    }else if(m_p2.getNumOfPieces() == 2)
    {
        setWinner(FIELDSTATE::PLAYER_1);
        return true;
    }
    return false;
}

/*
    setter za winnera
*/
void Game::setWinner(FIELDSTATE winner){
    this->winner = winner;
}


bool Game::isValidIndex(int i) const{
    return (i>=0 && i<NUM_OF_FIELDS);
}

FIELDSTATE Game::getWinner() const{
    return winner;
}

/*
 *  Implementacija meotde isValidToRemove: provera da li player sme da ukloni figuru sa polja i
 *  Metoda se poziva kada player napravil Mill
 *
 */
bool Game::isValidToRemove(int i, HumanPlayer &player) const{


    // Slucaj kada nije unet dobar indeks
    if (!isValidIndex(i))
    {
        std::cout << "Error in index" << std::endl;
        return false;
    }
    // ako polje nije prazno i ne zauzima ga player
    if(gameMap->boardFields[i].isOccupied() && gameMap->boardFields[i].getPlayerID() != player.id())
    {
        // Slucaj u kome je izabrano polje suprotnog igraca, polje je dozvoljeno da se ukloni ako:
        // 1. Ne pripada Millu
        // 2. Pripada Millu, ali igrac ima jos samo 3 figurice u igri
        int numOfPieces = player.id() == FIELDSTATE::PLAYER_1? m_p2.getNumOfPieces() : m_p1.getNumOfPieces();

        if (!checkMills(i) || numOfPieces == 3)
        {
            return true;
        }else{
            std::cout<< "You can't remove piece from the Mill just yet!" << std::endl;
            return false;
        }

    }
    return false;
}

bool Game::isValidToMove(int from, int to) const{

    if (!isValidIndex(from) || !isValidIndex(to)){
        return false;
    }

    auto neighbours = gameMap->boardFields[from].getNeighboursIndices();
    bool contains = (std::find(neighbours.begin(), neighbours.end(), to) != neighbours.end());

    // Ukoliko je izabrano polje prazno i sused je polja i

    return (!gameMap->boardFields[to].isOccupied() && contains);
}

bool Game::isValidToSelect(int i, HumanPlayer &player) const{

    return isValidIndex(i) && gameMap->boardFields[i].isOccupied() && gameMap->boardFields[i].getPlayerID() == player.id();

}


void Game::setup(){
    if(gameState != GAMESTATE::INIT){
        std::cout << "The has already been initialized" << std::endl;
        return;
    }

    m_p1.changeTurn(); //prvi je na potezu igrac 1
    gameMap->printMapTerminal();

    int i=0;
    while (i <= 2* NUM_OF_PIECES ){
        if (m_p1.turn()){
                while(!makeSetupMove(m_p1)) ;
                m_p1.changeTurn();
                m_p2.changeTurn();
        }else{
            while(!makeSetupMove(m_p2));
            m_p1.changeTurn();
            m_p2.changeTurn();
        }
        i++;

    } //end while
    std::cout << "The game has been set up!" << std::endl;
    std::cout << "Player 1 No. of pieces: " << m_p1.getNumOfPieces() << std::endl;
    std::cout << "Player 2 No. of pieces: " << m_p2.getNumOfPieces() << std::endl;

    gameMap->printMapTerminal();
    gameState = GAMESTATE::PLAY;


}

// Inicijalizuje neke gluposti vrv mozemo i bez ovoga, da se stavi u konstruktor npr
void Game::setup_graphical(){


    if(gameState != GAMESTATE::INIT){
        std::cout << "The has already been initialized" << std::endl;
        setMesssage("The game has already been initialized");
        return;
    }

    m_p1.changeTurn(); //prvi je na potezu igrac 1
    phase1_piece_counter = 2* NUM_OF_PIECES;
}

// Proverava da li su sve figurice postavljene i ako jesu zavrsava phase1
void Game::checkPhase1End()
{
    if(phase1_piece_counter == 0)
    {
        std::cout << "The game has been set up!" << std::endl;
        setMesssage("The game has been set up!");
        std::cout << "Player 1 No. of pieces: " << m_p1.getNumOfPieces() << std::endl;
        std::cout << "Player 2 No. of pieces: " << m_p2.getNumOfPieces() << std::endl;

        gameMap->printMapTerminal();
        gameState = GAMESTATE::PLAY;
    }
}

void Game::play(){
    if(gameState != GAMESTATE::PLAY){
        std::cout << "The game is not initialized" << std::endl;
        return;
    }
    std::cout << "PLAY PART" << std::endl;

    while(!gameOver())
    {

        if (m_p1.turn())
        {
            while(!makePlayMove(m_p1));
            gameMap->printMapTerminal();
            m_p1.changeTurn();
            m_p2.changeTurn();

        }else
        {
            while(!makePlayMove(m_p2));
            gameMap->printMapTerminal();
            m_p1.changeTurn();
            m_p2.changeTurn();
        }

    }// end while
    std:: cout << "The game is over"<< std::endl;
    if (getWinner() == FIELDSTATE::PLAYER_1)
    {
        std::cout << "PLAYER 1 is the winner" << std::endl;
    }else if (getWinner() == FIELDSTATE:: PLAYER_2)
    {
        std::cout << "PLAYER 1 is the winner" << std::endl;
    }else{
        std::cout << "Error"<< std::endl;
    }

}


QString Game::getMessage() const
{
    return message;
}

void Game::setMesssage(const std::string &msg)
{
    message.clear();
    message = message.fromStdString(msg);
}
