#include "gameai.h"
#include "gamemap.h"
#include "player.h"
#include "QGraphicsScene"

GameAI::GameAI(Player* p1, Player* p2)
    : Game(p1, p2),
      maxDepthAI(5),
      playerAI(FIELDSTATE::PLAYER_1)
{
    // ako igra AI prvi onda nakon sto inicijalizujemo igru u superu samo odigra prvi potez
    if(playerAI==FIELDSTATE::PLAYER_1)
    {
        std::pair<int,int> ret = max(maxDepthAI);
        std::cout<<ret.first<<" "<<ret.second<<std::endl;
    }
}


void GameAI::playMove(Player* player, int index, MyGraphicsScene *scene)
{
   // TODO: Treba mi provera mozda ovde koji je igrac da slucajno covek ne klikne brzo dok bot ne napravi potez, ali mozda i ne treba?
    Game::playMove(player, index, scene);

    // kad se zavrsi odigravanje protivnickog poteza, bot je na redu ako nije bio mill
    if(turnAI() && !Game::getMillOccured())
    {
        int depth = std::min(maxDepthAI, Game::getBoardPieces());
        std::pair<int,int> ret = max(depth);
        std::cout<<ret.first<<" "<<ret.second<<std::endl;
    }
}

bool GameAI::turnAI()
{
    if(playerAI==FIELDSTATE::PLAYER_1)
    {
        return Game::getPlayer1()->turn();
    }
    else
    {
        return Game::getPlayer2()->turn();
    }
}



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




