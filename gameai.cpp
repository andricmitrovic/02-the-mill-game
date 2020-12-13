#include "gameai.h"
#include "gamemap.h"
#include "humanplayer.h"
#include "QGraphicsScene"

GameAI::GameAI(HumanPlayer & p1, HumanPlayer & p2)
    : gameMap(new GameMap()), m_p1(p1), m_p2(p2), gameState(GAMESTATE::INIT),
      mill_occured(false), moveFrom(-1), boardPieces(2*NUM_OF_PIECES), winner(FIELDSTATE::EMPTY), maxDepthAI(5){}

GameAI::~GameAI() {
    delete gameMap;
}

bool GameAI::checkMills(unsigned index) const {
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
bool GameAI::makeSetupMove_graphical(HumanPlayer & player, unsigned i, QGraphicsScene &scene) {

    //std::cout << player.getName() << "'s turn:  Choose a field [a-x]: " << std::endl;
    setMessage(player.getName() + "'s turn:  Choose a field [a-x]: ");
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
        setMessage(player.getName() + " occupied a field.");

        //gameMap -> printMapTerminal();

        if (checkMills(i))
            mill_occured = true;
        return true;
    }

}

bool GameAI::makePlayMove_graphical(HumanPlayer & player, unsigned moveFrom, unsigned moveTo) {
    setMessage(player.getName() + "'s turn: Choose a piece to move!");

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

bool GameAI::removeOpponentsPiece_graphic(HumanPlayer & player, unsigned index) {

    if (!isValidToRemove(index, player))
    {
        setMessage("You can't remove this piece!" );
        return false;
    }
    gameMap -> getBoardFields()[index].deoccupy();

    player.id() == FIELDSTATE::PLAYER_1 ? m_p2.decNumOfPieces() : m_p1.decNumOfPieces(); // ????? Da ne treba mozda ovde obrnuto

    mill_occured = false;

    setMessage("Player " + player.getName() + " has lost a piece!");
    return true;
}
/*
    Implementacija metoda koji proverava da li je igra zavrsena
    Igra nije gotova sve dok jedan od igraca ne ostane sa dve figurice
*/

bool GameAI::gameOver() {
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
void GameAI::setWinner(FIELDSTATE winner) {
    this -> winner = winner;
}


FIELDSTATE GameAI::getWinner() const {
    return winner;
}

bool GameAI::isValidIndex(int i) const {
    return (i >= 0 && i < NUM_OF_FIELDS);
}

/*
 *  Implementacija meotde isValidToRemove: provera da li player sme da ukloni figuru sa polja i
 *  Metoda se poziva kada player napravil Mill
 *
 */
bool GameAI::isValidToRemove(int i, HumanPlayer & player) {

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

bool GameAI::isValidToMove(int from, int to) const {

    if (!isValidIndex(from) || !isValidIndex(to)) {
        return false;
    }

    auto neighbours = gameMap -> getBoardFields()[from].getNeighboursIndices();
    bool contains = (std::find(neighbours.begin(), neighbours.end(), to) != neighbours.end());

    // Ukoliko je izabrano polje prazno i sused je polja i

    return (!gameMap -> getBoardFields()[to].isOccupied() && contains);
}

bool GameAI::isValidToSelect(int i, HumanPlayer & player) const {
    return isValidIndex(i) && gameMap -> getBoardFields()[i].isOccupied() && gameMap -> getBoardFields()[i].getPlayerID() == player.id();
}

bool GameAI::isValidToOccupy(int i, HumanPlayer & player) const {
    return false;
}

void GameAI::changeTurn() {
    m_p1.changeTurn();
    m_p2.changeTurn();
}

void GameAI::playMove(HumanPlayer &player, int index, QGraphicsScene &scene)
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

HumanPlayer &GameAI::getCurrentPlayer(){
    return m_p1.turn()? m_p1 : m_p2;
}


// Inicijalizuje neke gluposti vrv mozemo i bez ovoga, da se stavi u konstruktor npr
void GameAI::setup_graphical() {
    if (gameState != GAMESTATE::INIT) {
        std::cout << "The has already been initialized" << std::endl;
        setMessage("The game has already been initialized");
        return;
    }

    m_p1.changeTurn(); //prvi je na potezu igrac 1
}

// Proverava da li su sve figurice postavljene i ako jesu zavrsava phase1

bool GameAI::checkPhase1End() {
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


QString GameAI::getMessage() const {
    return message;
}

void GameAI::setMessage(const std::string & msg){
    message.clear();
    message = message.fromStdString(msg);
}

void GameAI::makeSetupMove_AI(HumanPlayer & player, int i) {

    gameMap -> getBoardFields()[i].occupy(player.id());
    player.incNumOfPieces();

    if (checkMills(i))
    {
        mill_occured = true;
    }
}

void GameAI::revertSetupMove_AI(HumanPlayer & player, int i) {

    gameMap -> getBoardFields()[i].deoccupy();
    player.decNumOfPieces();

    mill_occured = false;

}

std::pair<int,int> GameAI::max(int depth)
{
    int maxValue = -2;
    int move = -1;

    // !!! TREBA MI HEURISTICKA PROCENA DA JE POTEZ OK AKO MOZE STO VISI MILLOVA DA SE SPOJI ODATLE U BUDUCNOSTI

    // ako m_p1 napravi mill pobedio je, ako m_p2 napravi mill izgubio je nagradu
    if (this->mill_occured)
    {
        // ako je pozivom maxa desio se mill to znaci da se on desio zapravo u minu i salje se -1 jer je to protivnikov najbolji potez
        return std::make_pair(-1, -1);
    }

    // ako je kraj postavljanja figurica vrati 0 jer nema milla i nikome nista
    if (this->checkPhase1End() || depth == 0)
    {
        return std::make_pair(0, -1);
    }

    // ako nije nista od odozgo ovih, odigraj sve moguce poteze i pozovi min() i azuriraj maxValue posle svakog poziva
    for(int field_num = 0; field_num < NUM_OF_FIELDS; field_num++)
    {
        if(this->gameMap->getBoardFields()[field_num].isOccupied())               // moram da kopiram gameMap kasnije ovde u zavisnosti koje je trenutno stanje igre ili samo i ovde da promenim stanje mape kad menjam i u pravoj
            continue;

        // odigraj potez
        this->makeSetupMove_AI(this->m_p1, field_num);

        // pozovi min
        std::pair<int,int> ret_val= min(depth-1);

        // azuriraj
        if(ret_val.first > maxValue )
        {
            maxValue = ret_val.first;
            move = field_num;
        }


        /*if(depth==5)
            std::cout<<"move_good? : "<<ret_val.first<<" "<<field_num<<std::endl;*/

        // vrati potez unazad, da li mogu da zloupotrebim neku funkciju ovde ili pravim novu?
        this->revertSetupMove_AI(this->m_p1, field_num);
    }
    return std::make_pair(maxValue, move);
}


std::pair<int,int> GameAI::min(int depth)
{
    int minValue = 2;
    //int move;

    // proveri da li je mill
    if (this->mill_occured)             // mozda treba da se obrne nagrada ovde jer kad se desi mill ne menja se turn?
    {
        return std::make_pair(1, -1);
    }

    // ako je kraj postavljanja figurica vrati 0 jer nema milla i nikome nista
    if (this->checkPhase1End() || depth == 0)
    {
        return std::make_pair(0, -1);
    }

    // ako nije nista od odozgo ovih, odigraj sve moguce poteze i pozovi min() i azuriraj maxValue posle svakog poziva
    for(int field_num = 0; field_num < NUM_OF_FIELDS; field_num++)
    {
        if(this->gameMap->getBoardFields()[field_num].isOccupied())               // moram da kopiram gameMap kasnije ovde u zavisnosti koje je trenutno stanje igre ili samo i ovde da promenim stanje mape kad menjam i u pravoj
            continue;

        // odigraj potez
        this->makeSetupMove_AI(this->m_p2, field_num);

        // pozovi min
        std::pair<int,int> ret_val= max(depth-1);

        // azuriraj
        if(ret_val.first < minValue )
        {
            minValue = ret_val.first;
        }

        // vrati potez unazad, da li mogu da zloupotrebim neku funkciju ovde ili pravim novu?
        this->revertSetupMove_AI(this->m_p2, field_num);
    }

    return std::make_pair(minValue, -1);
}




