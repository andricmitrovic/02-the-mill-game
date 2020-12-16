#include "gameai.h"
#include "gamemap.h"
#include "player.h"
#include "QGraphicsScene"

GameAI::GameAI(Player* p1, Player* p2)
    : Game(p1,p2),
      maxDepthAI(5)
{}

/*
void GameAI::playMove(Player &player, int index, QGraphicsScene &scene)
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
*/



void GameAI::makeSetupMove_AI(Player* player, int i) {

    Game::getGameMap() -> getBoardFields()[i].occupy(player->id());
    player->incNumOfPieces();

    if (checkMills(i))
    {
        Game::setMillOccured(true);
    }
}

void GameAI::revertSetupMove_AI(Player* player, int i) {

    Game::getGameMap() -> getBoardFields()[i].deoccupy();
    player->decNumOfPieces();

    Game::setMillOccured(false);

}

std::pair<int,int> GameAI::max(int depth)
{
    int maxValue = -2;
    int move = -1;

    // !!! TREBA MI HEURISTICKA PROCENA DA JE POTEZ OK AKO MOZE STO VISI MILLOVA DA SE SPOJI ODATLE U BUDUCNOSTI

    // ako m_p1 napravi mill pobedio je, ako m_p2 napravi mill izgubio je nagradu
    if (Game::getMillOccured())
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
        if(Game::getGameMap()->getBoardFields()[field_num].isOccupied())               // moram da kopiram gameMap kasnije ovde u zavisnosti koje je trenutno stanje igre ili samo i ovde da promenim stanje mape kad menjam i u pravoj
            continue;

        // odigraj potez
        this->makeSetupMove_AI(Game::getPlayer1(), field_num);

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
        this->revertSetupMove_AI(Game::getPlayer1(), field_num);
    }
    return std::make_pair(maxValue, move);
}


std::pair<int,int> GameAI::min(int depth)
{
    int minValue = 2;
    //int move;

    // proveri da li je mill
    if (Game::getMillOccured())             // mozda treba da se obrne nagrada ovde jer kad se desi mill ne menja se turn?
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
        if(Game::getGameMap()->getBoardFields()[field_num].isOccupied())               // moram da kopiram gameMap kasnije ovde u zavisnosti koje je trenutno stanje igre ili samo i ovde da promenim stanje mape kad menjam i u pravoj
            continue;

        // odigraj potez
        this->makeSetupMove_AI(Game::getPlayer2(), field_num);

        // pozovi min
        std::pair<int,int> ret_val= max(depth-1);

        // azuriraj
        if(ret_val.first < minValue )
        {
            minValue = ret_val.first;
        }

        // vrati potez unazad, da li mogu da zloupotrebim neku funkciju ovde ili pravim novu?
        this->revertSetupMove_AI(Game::getPlayer2(), field_num);
    }

    return std::make_pair(minValue, -1);
}




