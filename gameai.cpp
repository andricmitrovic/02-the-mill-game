#include "gameai.h"
#include "gamemap.h"
#include "player.h"
#include "QGraphicsScene"

GameAI::GameAI(Player* p1, Player* p2)
    : Game(p1,p2),
      maxDepthPhase1(5),
      maxDepthPhase2(5),
      playerAI(FIELDSTATE::PLAYER_2)
{}


void GameAI::playMove(Player* player, int index, MyGraphicsScene *scene)
{
    // Provera ovde koji je igrac da slucajno covek ne klikne brzo dok bot ne napravi potez
    if(player == getPlayerHuman())
    {
        // Human igra potez
        Game::playMove(player, index, scene);
        return;
    }

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
                playMovingMoveAI(scene);
            }

            //std::cout<<Game::getPlayer1()->getNumOfPieces()<<" "<<Game::getPlayer2()->getNumOfPieces()<<std::endl;
        }

        // ako je bot napravio mill onda pokrece sledeci korak da vidi sta jede
        if(Game::getMillOccured())
        {
            playMillAI(scene);

            //std::cout<<Game::getPlayer1()->getNumOfPieces()<<" "<<Game::getPlayer2()->getNumOfPieces()<<std::endl;
        }
    }

    // TODO!!!!!!!!!!!! proveri kraj partije nekad negde ako treba kad bot igra jer je glup pa ne zna da je kraj
    // takodje ne radi kad human igrac nema gde da pomeri vise ne kaze da je game over, mozda bi bug i za bota ispao, vrv je to ono kad mi kaze -1:-1:2

    // !!! ispise gluposti kada bot izgubi ili kada nema sta da igra

    // takodje ima bug kod humana kad mora micu da jede botu ali radi u lokalu

    // Todo kad blokira ili zauzima da preferira centralna polja

    // kda jede u drugoj fazi a mozda i u prvoj, jedi one koje prave mill pomeranjem figurica

    // todo kad jedes u drugoj fazi msm da treba samo da pojede figure koje spajaju mill u sledecem potezu protivnika

    // todo: heuristika u fazi 2 moze biti samo to ko je pobedio a ako dodje do dubine onda stanje igre tj odnos figurica za pocetak pa kasnije mozda nesto advanced vise

    // bug: ako minimax pocne da simulira igru i kojoj nema vise nista da se igra zabosce cak i ako nije jos gotovo ali bice sigurno
}

void GameAI::playSetupMoveAI(MyGraphicsScene *scene)
{
    std::pair<int,int> retVal = maxSetup(maxDepthPhase1, getBoardPieces(), INT32_MIN, INT32_MAX);
    std::cout<<"Bot igra na: "<<retVal.second<<", zbog nagrade od: "<<retVal.first<<std::endl;
    Game::playMove(getPlayerAI(), retVal.second, scene);
}

void GameAI::playMovingMoveAI(MyGraphicsScene *scene)
{
    std::tuple<int,int, int> retVal = maxPlay(maxDepthPhase2, INT32_MIN, INT32_MAX);
    std::cout<<"Bot igra "<<std::get<1>(retVal)<<":"<<std::get<2>(retVal)<<", zbog nagrade od "<<std::get<0>(retVal)<<std::endl;

    Game::setMoveFrom(std::get<1>(retVal));
    Game::playMove(getPlayerAI(), std::get<2>(retVal), scene);
}

void GameAI::playMillAI(MyGraphicsScene *scene)
{
    // stavimo false da bi radio minimax
    Game::setMillOccured(false);

    int depth = std::min(maxDepthPhase1, Game::getBoardPieces());

    int maxValue = INT32_MIN;
    int move = -1;
    int retVal = -1;

    // onda pokrenem MIN jer protivnik igra, iz svake moguce obrisane figurice na stolu tj svake protivnikove figure
    for(int field_num = 0; field_num < NUM_OF_FIELDS; field_num++)
    {
        // ako je protivnikova figurica tu i smes da jedes nju
        if(isValidToRemove(field_num, getPlayerAI()))
        {
            // obrisi tu figuricu
            Game::getGameMap() -> getBoardFields()[field_num].deoccupy();

            //pokreni MIN onaj u zavisnosti od stanja igre tj kakve poteze igraju protivnici dalje
            if(Game::getGameState()==GAMESTATE::INIT)
            {
                retVal = std::get<0>(minSetup(depth, Game::getBoardPieces(), INT32_MIN, INT32_MAX));
            }
            else
            {
                retVal = std::get<0>(minPlay(maxDepthPhase1, INT32_MIN, INT32_MAX));
                //std::cout<<field_num<<" "<<retVal<<std::endl;
            }

            //azuriraj vrednosti
            if(retVal > maxValue )
            {
                maxValue = retVal;
                move = field_num;
            }

            //vrati tu figuricu
            Game::getGameMap() -> getBoardFields()[field_num].occupy(getHumanFieldstate());
        }
    }

    std::cout<<"Bot jede: "<<move<<", zbog nagrade od: "<<maxValue<<std::endl;

    // vratimo true da bi radio playMove
    Game::setMillOccured(true);
    Game::playMove(getPlayerAI(), move, scene);
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

// Phase 2 minimax
void GameAI::makePlayMoveAI(Player* player, int moveFrom, int moveTo)
{
    //if (Game::isValidToMove(moveFrom, moveTo))

    Game::getGameMap() -> getBoardFields()[moveFrom].deoccupy();
    Game::getGameMap() -> getBoardFields()[moveTo].occupy(player->id() == FIELDSTATE::PLAYER_1 ? FIELDSTATE::PLAYER_1 : FIELDSTATE::PLAYER_2);

    if (checkMills(moveTo))
        Game::setMillOccured(true);
}
void GameAI::revertPlayMoveAI(Player* player, int moveTo, int moveFrom) // obrnuo sam ovde da bi u minimaxu se istim redom slali podaci
{
    Game::getGameMap() -> getBoardFields()[moveFrom].deoccupy();
    Game::getGameMap() -> getBoardFields()[moveTo].occupy(player->id() == FIELDSTATE::PLAYER_1 ? FIELDSTATE::PLAYER_1 : FIELDSTATE::PLAYER_2);

    Game::setMillOccured(false);
}

std::tuple<int, int,int> GameAI::maxPlay(int depth, int alfa, int beta)
{
    int maxValue = INT32_MIN;
    int moveFrom = -1;
    int moveTo = -1;
    Player* player = getPlayerAI();

    // ako Human napravi mill: -1
    if (Game::getMillOccured())
    {
        // ako je pozivom maxa desio se mill to znaci da se on desio zapravo u minu i salje se -1 jer je to protivnikov najbolji potez

        // ista fora kao u Setup, ako vec gubis izgubi najbolje moguce npr. blokiraj mu mill da ne moze da ga ponavlja u nedogled
        return std::make_tuple(-depth, -1, -1);
    }

    // ako je dosao do dubine nikom nista, da li moze nesto drugo da bude 0?
    if (depth == 0)
    {
        return std::make_tuple(0, -1, -1);
    }

    // ako nije nista od odozgo ovih, odigraj sve moguce poteze i pozovi min() i azuriraj maxValue posle svakog poziva
    for(int field_num = 0; field_num < NUM_OF_FIELDS; field_num++)
    {
        // ako je AI figurica na ovom polju, pokreni potez iz svakog moguceg slobodnog suseda
        if(Game::getGameMap()->getBoardFields()[field_num].getPlayerID() == playerAI)
        {
            for(int adj_field_num: Game::getGameMap()->getBoardFields()[field_num].getNeighboursIndices())
            {
                // ako je susedno polje slobodno mozes dalje da radis
                if(Game::getGameMap()->getBoardFields()[adj_field_num].getPlayerID() != FIELDSTATE::EMPTY)
                    continue;



                // odigraj potez, tj pomeri sa jednog polja na drugo
                this->makePlayMoveAI(player, field_num, adj_field_num);

                // pozovi min
                std::tuple<int,int,int> ret_val= minPlay(depth-1, alfa, beta);

                // azuriraj
                if(std::get<0>(ret_val) > maxValue )
                {
                    maxValue = std::get<0>(ret_val);
                    moveFrom = field_num;
                    moveTo = adj_field_num;
                }

                // vrati potez unazad
                this->revertPlayMoveAI(player, field_num, adj_field_num);

                // alfa beta odsecanje
                if(maxValue >= beta)
                {
                    // ovaj je sigurno gori nego neki dosadasnji u minu pa je nebitno polje
                    return std::make_tuple(maxValue, -1, -1);
                }

                if(maxValue > alfa)
                {
                    alfa = maxValue;
                }

                /*if(depth==maxDepthAI)
                {
                    std::cout<<field_num<<":"<<adj_field_num<<":N"<<std::get<0>(ret_val)<<std::endl;
                }*/
            }
        }
    }
    return std::make_tuple(maxValue, moveFrom, moveTo);
}

std::tuple<int, int,int> GameAI::minPlay(int depth, int alfa, int beta)
{
    int minValue = INT32_MAX;
    int moveFrom = -1;
    int moveTo = -1;
    Player* player = getPlayerHuman();

    // ako pobedis: +beskonacno, ne mora mozda
    // ako izgubis: -beskonacno, ne mora mozda

    // ako Human napravi mill: umesto 1, nagrada nek bude da sto pre napravi mill da ne bi beskonacno igrao neke poteze
    if (Game::getMillOccured())
    {
        // nagrada je dubina, sto je veca jer se smanjuje znaci da je u visem delu grafa
        return std::make_tuple(depth+1, -1, -1);
    }

    // ako je dosao do dubine nikom nista, da li moze nesto drugo da bude 0?
    if (depth == 0)
    {
        return std::make_tuple(0, -1, -1);
    }

    // ako nije nista od odozgo ovih, odigraj sve moguce poteze i pozovi min() i azuriraj maxValue posle svakog poziva
    for(int field_num = 0; field_num < NUM_OF_FIELDS; field_num++)
    {
        // ako je Human figurica na ovom polju, pokreni potez iz svakog moguceg slobodnog suseda
        if(Game::getGameMap()->getBoardFields()[field_num].getPlayerID() == getHumanFieldstate())
        {
            for(int adj_field_num: Game::getGameMap()->getBoardFields()[field_num].getNeighboursIndices())
            {
                // ako je susedno polje slobodno mozes dalje da radis
                if(Game::getGameMap()->getBoardFields()[adj_field_num].getPlayerID() != FIELDSTATE::EMPTY)
                    continue;

                // odigraj potez, tj pomeri sa jednog polja na drugo
                this->makePlayMoveAI(player, field_num, adj_field_num);

                // pozovi min
                std::tuple<int,int,int> ret_val= maxPlay(depth-1, alfa, beta);

                // azuriraj
                if(std::get<0>(ret_val) < minValue )
                {
                    minValue = std::get<0>(ret_val);
                    moveFrom = field_num;
                    moveTo = adj_field_num;
                }

                // vrati potez unazad
                this->revertPlayMoveAI(player, field_num, adj_field_num);

                // alfa beta odsecanje
                if(minValue <= alfa)
                {
                    // ovaj je sigurno gori nego neki dosadasnji u minu pa je nebitno polje
                    return std::make_tuple(minValue, -1, -1);
                }

                if(minValue < beta)
                {
                    beta = minValue;
                }
            }
        }
    }
    return std::make_tuple(minValue, moveFrom, moveTo);
}

// Phase 1 minimax

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

int GameAI::heuristicSetup(FIELDSTATE player)
{
    int reward = 0;

    // recimo heuristika moze biti koliko polja ima koji igrac slobodnih da puca za mill?
    // tako teramo bota da uzima polja koja pokrivaju i blokiraju veci broj linija

    // ako ces stavljati negde stavi u red u kome se nalazi human figura a nema ai figure tako da pokrivas sto vise slobodnih linija sa tog polja

    // procenjujemo tablu za AI igraca

    std::vector<int> interrsections{4, 10, 13, 19};
    std::vector<int> sides{1, 9, 14, 22, 7, 11, 12, 16};


    for(int index = 0; index < NUM_OF_FIELDS; index++)
    {
        if(Game::getGameMap()->getBoardFields()[index].getPlayerID() == player)
        {
            // preuzeto iz checkMillsa, modifikovati tako da odredi nagradu u odnosu susede u millu

            unsigned checkIndex1 = Game::getGameMap()-> getBoardFields()[index].getMills().first.first;
            unsigned checkIndex2 = Game::getGameMap()-> getBoardFields()[index].getMills().first.second;

            unsigned checkIndex3 = Game::getGameMap() -> getBoardFields()[index].getMills().second.first;
            unsigned checkIndex4 = Game::getGameMap() -> getBoardFields()[index].getMills().second.second;

            // index je igraceva figurica

            // 1. Ako su druga dva polja praza super
            if (Game::getGameMap() -> getBoardFields()[checkIndex1].getPlayerID() == FIELDSTATE::EMPTY && Game::getGameMap() -> getBoardFields()[checkIndex2].getPlayerID() == FIELDSTATE::EMPTY)
            {
                if(find(std::begin(interrsections), std::end(interrsections), index) != std::end(interrsections))
                    reward+=10;
                else if(find(std::begin(sides), std::end(sides), index) != std::end(sides))
                    reward+=5;
                else
                    reward+=1;
            }

            if (Game::getGameMap() -> getBoardFields()[checkIndex3].getPlayerID() == FIELDSTATE::EMPTY && Game::getGameMap() -> getBoardFields()[checkIndex4].getPlayerID() == FIELDSTATE::EMPTY)
            {
                if(find(std::begin(interrsections), std::end(interrsections), index) != std::end(interrsections))
                    reward+=10;
                else if(find(std::begin(sides), std::end(sides), index) != std::end(sides))
                    reward+=5;
                else
                    reward+=1;
            }

            // 2. Ako je jedno prazno a drugo tvoje SUPER

            if ((Game::getGameMap() -> getBoardFields()[checkIndex1].getPlayerID() == FIELDSTATE::EMPTY && Game::getGameMap() -> getBoardFields()[checkIndex2].getPlayerID() == player) || \
                (Game::getGameMap() -> getBoardFields()[checkIndex1].getPlayerID() == player && Game::getGameMap() -> getBoardFields()[checkIndex2].getPlayerID() == FIELDSTATE::EMPTY) )
            {
                if(find(std::begin(interrsections), std::end(interrsections), index) != std::end(interrsections))
                    reward+=1000;
                else if(find(std::begin(sides), std::end(sides), index) != std::end(sides))
                    reward+=500;
                else
                    reward+=100;
            }

            if ((Game::getGameMap() -> getBoardFields()[checkIndex3].getPlayerID() == FIELDSTATE::EMPTY && Game::getGameMap() -> getBoardFields()[checkIndex4].getPlayerID() == player) || \
                (Game::getGameMap() -> getBoardFields()[checkIndex3].getPlayerID() == player && Game::getGameMap() -> getBoardFields()[checkIndex4].getPlayerID() == FIELDSTATE::EMPTY) )
            {
                if(find(std::begin(interrsections), std::end(interrsections), index) != std::end(interrsections))
                    reward+=1000;
                else if(find(std::begin(sides), std::end(sides), index) != std::end(sides))
                    reward+=500;
                else
                    reward+=100;
            }


            // 3. Ako je jedno tvoje a drugo protivnicko, meh

            // 4. Ako je jedno prazno, a drugo protivnicko ok blokirao si ga

            /* Tips:
               Any piece surrounded by your opponent's pieces is useless.                               inc reward = 0
               Intersections are the most valuable locations, since they have four adjacent spaces.     inc reward x10
               Corners are weakest, since they only have two adjacent spaces.                           inc reward x1
               Sides are stronger than corners, as they have three adjacent spaces.                     inc reward x5
            */



            }
        }

    return reward;
}

std::pair<int,int> GameAI::maxSetup(int depth, int remainingPieces, int alfa, int beta)
{
    int maxValue = INT32_MIN;
    int move = -1;
    Player* player = getPlayerAI();
    int reward = 0;

    // ako m_p1 napravi mill pobedio je, ako m_p2 napravi mill izgubio je nagradu
    if (Game::getMillOccured())
    {
        if (depth == 0)
        {
            return std::make_pair(-1000, -1);
        }

        Game::setMillOccured(false);

        int retVal = -1;

        // onda pokrenem MIN jer protivnik igra, iz svake moguce obrisane figurice na stolu tj svake protivnikove figure
        for(int field_num = 0; field_num < NUM_OF_FIELDS; field_num++)
        {
            // ako je protivnikova figurica tu i smes da jedes nju
            if(isValidToRemove(field_num, getPlayerHuman()))
            {
                // obrisi tu figuricu
                Game::getGameMap() -> getBoardFields()[field_num].deoccupy();

                retVal = std::get<0>(maxSetup(depth-1, Game::getBoardPieces(), INT32_MIN, INT32_MAX));

                //azuriraj vrednosti
                if(retVal > maxValue )
                {
                    maxValue = retVal;
                    move = field_num;
                }
                //vrati tu figuricu
                Game::getGameMap() -> getBoardFields()[field_num].occupy(playerAI);

                if(maxValue >= beta)
                {
                    // ovaj je sigurno gori nego neki dosadasnji u minu pa je nebitno polje
                    //Game::setMillOccured(true);
                    return std::make_pair(maxValue, -1);
                }

                if(maxValue > alfa)
                {
                    alfa = maxValue;
                }



            }
        }

        // vratimo true da bi radio playMove
        //Game::setMillOccured(true);
        return std::make_pair(-maxValue, move);
    }

    // ako je kraj postavljanja figurica vrati 0 jer nema milla i nikome nista

    if( remainingPieces== 0 )
    {
        std::tuple<int,int,int> retVal = minPlay(maxDepthPhase2, alfa, beta);
        return std::make_pair(std::get<0>(retVal), -1);
    }

    if (depth <= 0)
    {
        reward = heuristicSetup(getHumanFieldstate());
        return std::make_pair(-reward, -1);
    }

    // ako nije nista od odozgo ovih, odigraj sve moguce poteze i pozovi min() i azuriraj maxValue posle svakog poziva
    for(int field_num = 0; field_num < NUM_OF_FIELDS; field_num++)
    {
        if(Game::getGameMap()->getBoardFields()[field_num].isOccupied())
            continue;

        // odigraj potez
        this->makeSetupMoveAI(player, field_num);

        // pozovi min
        std::pair<int,int> ret_val= minSetup(depth-1, remainingPieces-1, alfa, beta);

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


std::pair<int,int> GameAI::minSetup(int depth, int remainingPieces, int alfa, int beta)
{
    int minValue = INT32_MAX;
    //int move;
    Player* player = getPlayerHuman();
    int reward = 0;

    // proveri da li je mill
    if (Game::getMillOccured())             // mozda treba da se obrne nagrada ovde jer kad se desi mill ne menja se turn?
    {
        return std::make_pair(10000*depth, -1);
    }

    // ako je kraj postavljanja figurica vrati 0 jer nema milla i nikome nista

    if( remainingPieces== 0 )
    {
        //Todo
        //std::cout<<"MIN"<<std::endl;
        std::tuple<int,int,int> retVal = maxPlay(maxDepthPhase2, alfa, beta);
        return std::make_pair(std::get<0>(retVal), -1);
    }

    if( depth <= 0 )
    {
        reward = heuristicSetup(playerAI);
        return std::make_pair(reward, -1);
    }

    // ako nije nista od odozgo ovih, odigraj sve moguce poteze i pozovi min() i azuriraj maxValue posle svakog poziva
    for(int field_num = 0; field_num < NUM_OF_FIELDS; field_num++)
    {
        if(Game::getGameMap()->getBoardFields()[field_num].isOccupied())               // moram da kopiram gameMap kasnije ovde u zavisnosti koje je trenutno stanje igre ili samo i ovde da promenim stanje mape kad menjam i u pravoj
            continue;

        // odigraj potez
        this->makeSetupMoveAI(player, field_num);

        // pozovi min
        std::pair<int,int> ret_val= maxSetup(depth-1, remainingPieces-1,alfa, beta);

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




