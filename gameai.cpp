#include "gameai.h"
#include "gamemap.h"
#include "player.h"
#include "QGraphicsScene"

GameAI::GameAI(Player* p1, Player* p2)
    : Game(p1,p2),
      maxDepthAI(5),
      playerAI(FIELDSTATE::PLAYER_2)
{
    // ako igra AI prvi onda nakon sto inicijalizujemo igru u superu samo odigra prvi potez
    if(playerAI==FIELDSTATE::PLAYER_1)
    {
        std::pair<int,int> ret = maxSetup(maxDepthAI, -2, 2);
        std::cout<<"Bot igra na: "<<ret.second<<", zbog nagrade od: "<<ret.first<<std::endl;

        //Game::playMove(getPlayerAI(), ret.second, scene);
        /* ovde je problemcic sto mi fali scena da bih odradio first move,
         pa bi morala posebna funkcija da se zove u board.cpp nakon sto se scena iscrta da bot odigra*/
    }
}


void GameAI::playMove(Player* player, int index, QGraphicsScene &scene)
{
    // Provera ovde koji je igrac da slucajno covek ne klikne brzo dok bot ne napravi potez
    if(player != getPlayerHuman())
        return;
    // Human igra potez
    Game::playMove(player, index, scene);

    // Kad se zavrsi odigravanje Human poteza AI je na redu
    if(turnAI())
    {
        if(!Game::getMillOccured())
        {
            if(Game::getGameState()==GAMESTATE::INIT)
            {
                playSetupMoveAI(scene);
            }
            else
            {
                //todo
                //playMovingMoveAI(scene);
            }
        }

        // ako je bot napravio mill onda pokrece sledeci korak da vidi sta jede
        if(Game::getMillOccured())
        {
            if(Game::getGameState()==GAMESTATE::INIT)
            {
                playMillSetupAI(scene);
            }
            else
            {
                //todo
                //playMillMovingAI(scene);
            }
        }
        //std::cout<<Game::getMillOccured()<<std::endl;//<<std::flush;
    }
}

void GameAI::playSetupMoveAI(QGraphicsScene &scene)
{
    int depth = std::min(maxDepthAI, Game::getBoardPieces());
    //std::cout<<depth<<std::endl;
    std::pair<int,int> retVal = maxSetup(depth, -2, 2);
    std::cout<<"Bot igra na: "<<retVal.second<<", zbog nagrade od: "<<retVal.first<<std::endl;
    Game::playMove(getPlayerAI(), retVal.second, scene);
}

void GameAI::playMillSetupAI(QGraphicsScene &scene)
{
    // stavimo false da bi radio minimax
    Game::setMillOccured(false);

    int depth = std::min(maxDepthAI, Game::getBoardPieces());
    //std::cout<<depth<<std::endl;

    int maxValue = -2;
    int move = -1;

    // onda pokrenem MIN jer protivnik igra, iz svake moguce obrisane figurice na stolu tj svake protivnikove figure
    for(int field_num = 0; field_num < NUM_OF_FIELDS; field_num++)
    {
        // ako je protivnikova figurica tu i smes da jedes nju
        if(isValidToRemove(field_num, getPlayerAI()))
        {
            // obrisi tu figuricu
            Game::getGameMap() -> getBoardFields()[field_num].deoccupy();

            //pokreni MIN
            std::pair<int,int> retVal = minSetup(depth, -2, 2);

            //azuriraj vrednosti
            if(retVal.first > maxValue )
            {
                maxValue = retVal.first;
                move = field_num;
            }

            //vrati tu figuricu
            Game::getGameMap() -> getBoardFields()[field_num].occupy(getHumanFieldstate());
        }
    }

    std::cout<<"Bot bi da jede: "<<move<<", zbog nagrade od: "<<maxValue<<std::endl;

    // vratimo true da bi radio playMove
    Game::setMillOccured(true);
    Game::playMove(getPlayerAI(), move, scene);
}

void GameAI::playMovingMoveAI(QGraphicsScene &scene)
{
    // TODO

    // ideja: uzmem svaku AIovu figuricu i pomerim u svakom smeru koji moze i pokrenem minimax drugi jer onaj prvi radi samo za postavlanje figura


    return;
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

Player* GameAI::getPlayerAI()
{
    if(playerAI==FIELDSTATE::PLAYER_1)
    {
        return Game::getPlayer1();
    }
    else
    {
        return Game::getPlayer2();
    }
}

Player* GameAI::getPlayerHuman()
{
    if(playerAI==FIELDSTATE::PLAYER_1)
    {
        return Game::getPlayer2();
    }
    else
    {
        return Game::getPlayer1();
    }
}

FIELDSTATE GameAI::getHumanFieldstate()
{
    if(playerAI==FIELDSTATE::PLAYER_1)
    {
        return FIELDSTATE::PLAYER_2;
    }
    else
    {
        return FIELDSTATE::PLAYER_1;
    }
}



void GameAI::makeSetupMoveAI(Player* player, int i) {

    Game::getGameMap() -> getBoardFields()[i].occupy(player->id());
    player->incNumOfPieces();

    if (checkMills(i))
    {
        Game::setMillOccured(true);
    }
}

void GameAI::revertSetupMoveAI(Player* player, int i) {

    Game::getGameMap() -> getBoardFields()[i].deoccupy();
    player->decNumOfPieces();

    Game::setMillOccured(false);

}

std::pair<int,int> GameAI::maxSetup(int depth, int alfa, int beta)
{
    int maxValue = -2;
    int move = -1;
    Player* player = getPlayerAI();

    // !!! TREBA MI HEURISTICKA PROCENA DA JE POTEZ OK AKO MOZE STO VISI MILLOVA DA SE SPOJI ODATLE U BUDUCNOSTI
    // ako ces stavljati negde stavi u red u kome se nalazi human figura a nema ai figure tako da pokrivas sto vise slobodnih linija sa tog polja

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
        this->makeSetupMoveAI(player, field_num);

        // pozovi min
        std::pair<int,int> ret_val= minSetup(depth-1, -2, 2);

        // azuriraj
        if(ret_val.first > maxValue )
        {
            maxValue = ret_val.first;
            move = field_num;
        }

        // vrati potez unazad, da li mogu da zloupotrebim neku funkciju ovde ili pravim novu?
        this->revertSetupMoveAI(player, field_num);

        // alfa beta odsecanje
        if(maxValue >= beta)
        {
            // ovaj je sigurno gori nego neki dosadasnji u minu pa je nebitno polje
            return std::make_pair(maxValue, -1);
        }

        if(maxValue > alfa)
        {
            alfa = maxValue;
        }
    }
    return std::make_pair(maxValue, move);
}


std::pair<int,int> GameAI::minSetup(int depth, int alfa, int beta)
{
    int minValue = 2;
    //int move;
    Player* player = getPlayerHuman();

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
        this->makeSetupMoveAI(player, field_num);

        // pozovi min
        std::pair<int,int> ret_val= maxSetup(depth-1, -2, 2);

        // azuriraj
        if(ret_val.first < minValue )
        {
            minValue = ret_val.first;
        }

        // vrati potez unazad, da li mogu da zloupotrebim neku funkciju ovde ili pravim novu?
        this->revertSetupMoveAI(player, field_num);

        // alfa beta odsecanje
        if(minValue <= alfa)
        {
            // ovaj je sigurno gori nego neki dosadasnji u minu pa je nebitno polje
            return std::make_pair(minValue, -1);
        }

        if(minValue < beta)
        {
            beta = minValue;
        }
    }

    return std::make_pair(minValue, -1);
}




