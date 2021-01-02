#include "code/include/GameAi.h"
#include "code/include/GameMap.h"
#include "code/include/Player.h"
#include "code/include/MyGraphicsScene.h"

GameAI::GameAI(Player* p1, Player* p2)
    : Game(p1,p2),
      playerAI(FIELDSTATE::PLAYER_2)
{}


void GameAI::playMove(Player* player, int index, MyGraphicsScene *scene)
{
    // Humans turn
    if(player == getPlayerHuman())
    {
        Game::playMove(player, index, scene);
        return;
    }

    // AIs turn
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
        }

        // AI made a mill so it checks which piece to eat
        if(Game::getMillOccured())
        {
            playMillAI(scene);
        }
    }
}

void GameAI::playSetupMoveAI(MyGraphicsScene *scene)
{
    std::pair<int,int> retVal = maxSetup(maxDepthPhase1, getBoardPieces(), INT32_MIN, INT32_MAX);

    std::string msg = "AI played on " + std::to_string(retVal.second);
    Game::setGameMessage(msg);

    Game::playMove(getPlayerAI(), retVal.second, scene);
}

void GameAI::playMovingMoveAI(MyGraphicsScene *scene)
{
    std::tuple<int,int, int> retVal = maxPlay(maxDepthPhase2, INT32_MIN, INT32_MAX);

    std::string msg = "AI moved piece from " + std::to_string(std::get<1>(retVal)) + " to " + std::to_string(std::get<2>(retVal));
    Game::setGameMessage(msg);

    Game::setMoveFrom(std::get<1>(retVal));
    Game::playMove(getPlayerAI(), std::get<2>(retVal), scene);
}

void GameAI::playMillAI(MyGraphicsScene *scene)
{
    // Set false so the minimax after eating can work
    Game::setMillOccured(false);

    int depth = std::min(maxDepthPhase1, Game::getBoardPieces());

    int maxValue = INT32_MIN;
    int move = -1;
    int retVal = -1;

    // Delete every possible piece and continue game from there
    for(int field_num = 0; field_num < NUM_OF_FIELDS; field_num++)
    {
        if(isValidToRemove(field_num, getPlayerAI(), 0))
        {
            Game::getGameMap() -> getBoardFields()[field_num].deoccupy();

            if(Game::getGameState()==GAMESTATE::INIT)
            {
                retVal = std::get<0>(minSetup(depth, Game::getBoardPieces(), INT32_MIN, INT32_MAX));
            }
            else
            {
                retVal = std::get<0>(minPlay(maxDepthPhase1, INT32_MIN, INT32_MAX));
            }

            if(retVal > maxValue )
            {
                maxValue = retVal;
                move = field_num;
            }

            Game::getGameMap() -> getBoardFields()[field_num].occupy(getHumanFieldstate());
        }
    }

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

    // Huge negative for losing, huge positive for winning
    if(Game::gameOver())
    {
        if(Game::getWinner()==getHumanFieldstate())
            return std::make_tuple(-1000000, -1, -1);
        if(Game::getWinner()==playerAI)
            return std::make_tuple(1000000, -1, -1);
    }

    // Human player made a mill so negative reward
    if (Game::getMillOccured())
    {
        return std::make_tuple(-depth, -1, -1);
    }

    if (depth == 0)
    {
        return std::make_tuple(0, -1, -1);
    }

    // Try every possible move and continue trying from there
    for(int field_num = 0; field_num < NUM_OF_FIELDS; field_num++)
    {
        if(Game::getGameMap()->getBoardFields()[field_num].getPlayerID() == playerAI)
        {
            for(int adj_field_num: Game::getGameMap()->getBoardFields()[field_num].getNeighboursIndices())
            {
                if(Game::getGameMap()->getBoardFields()[adj_field_num].getPlayerID() != FIELDSTATE::EMPTY)
                    continue;

                this->makePlayMoveAI(player, field_num, adj_field_num);

                std::tuple<int,int,int> ret_val= minPlay(depth-1, alfa, beta);

                if(std::get<0>(ret_val) > maxValue )
                {
                    maxValue = std::get<0>(ret_val);
                    moveFrom = field_num;
                    moveTo = adj_field_num;
                }

                this->revertPlayMoveAI(player, field_num, adj_field_num);

                if(maxValue >= beta)
                {
                    return std::make_tuple(maxValue, -1, -1);
                }

                if(maxValue > alfa)
                {
                    alfa = maxValue;
                }
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

    // Huge negative for losing, huge positive for winning
    if(Game::gameOver())
    {
        if(Game::getWinner()==getHumanFieldstate())
            return std::make_tuple(-1000000, -1, -1);
        if(Game::getWinner()==playerAI)
            return std::make_tuple(1000000, -1, -1);
    }

    // AI player made a mill
    if (Game::getMillOccured())
    {
        return std::make_tuple(depth+1, -1, -1);
    }

    if (depth == 0)
    {
        return std::make_tuple(0, -1, -1);
    }

    // Try every possible move and continue trying from there
    for(int field_num = 0; field_num < NUM_OF_FIELDS; field_num++)
    {
        if(Game::getGameMap()->getBoardFields()[field_num].getPlayerID() == getHumanFieldstate())
        {
            for(int adj_field_num: Game::getGameMap()->getBoardFields()[field_num].getNeighboursIndices())
            {
                if(Game::getGameMap()->getBoardFields()[adj_field_num].getPlayerID() != FIELDSTATE::EMPTY)
                    continue;

                this->makePlayMoveAI(player, field_num, adj_field_num);

                std::tuple<int,int,int> ret_val= maxPlay(depth-1, alfa, beta);

                if(std::get<0>(ret_val) < minValue )
                {
                    minValue = std::get<0>(ret_val);
                    moveFrom = field_num;
                    moveTo = adj_field_num;
                }

                this->revertPlayMoveAI(player, field_num, adj_field_num);

                if(minValue <= alfa)
                {
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

int GameAI::heuristicSetup()
{
    int reward = 0;
    FIELDSTATE player = playerAI;

    std::vector<int> interrsections{4, 10, 13, 19};
    std::vector<int> sides{1, 9, 14, 22, 7, 11, 12, 16};


    for(int index = 0; index < NUM_OF_FIELDS; index++)
    {
        player = playerAI;

        if(Game::getGameMap()->getBoardFields()[index].getPlayerID() == player)
        {
            // For each AI piece get a big reward which serves as counting number of pieces
            reward += 10000;

            unsigned checkIndex1 = Game::getGameMap()-> getBoardFields()[index].getMills().first.first;
            unsigned checkIndex2 = Game::getGameMap()-> getBoardFields()[index].getMills().first.second;

            unsigned checkIndex3 = Game::getGameMap() -> getBoardFields()[index].getMills().second.first;
            unsigned checkIndex4 = Game::getGameMap() -> getBoardFields()[index].getMills().second.second;

            // Two other fields are empty, small rewards vary on the field position
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

            // One field is empty and other one is AIs, rewards vary on the field position

            if ((Game::getGameMap() -> getBoardFields()[checkIndex1].getPlayerID() == FIELDSTATE::EMPTY && Game::getGameMap() -> getBoardFields()[checkIndex2].getPlayerID() == player) || \
                (Game::getGameMap() -> getBoardFields()[checkIndex1].getPlayerID() == player && Game::getGameMap() -> getBoardFields()[checkIndex2].getPlayerID() == FIELDSTATE::EMPTY) )
            {
                if(find(std::begin(interrsections), std::end(interrsections), index) != std::end(interrsections))
                    reward+=100;
                else if(find(std::begin(sides), std::end(sides), index) != std::end(sides))
                    reward+=50;
                else
                    reward+=10;
            }

            if ((Game::getGameMap() -> getBoardFields()[checkIndex3].getPlayerID() == FIELDSTATE::EMPTY && Game::getGameMap() -> getBoardFields()[checkIndex4].getPlayerID() == player) || \
                (Game::getGameMap() -> getBoardFields()[checkIndex3].getPlayerID() == player && Game::getGameMap() -> getBoardFields()[checkIndex4].getPlayerID() == FIELDSTATE::EMPTY) )
            {
                if(find(std::begin(interrsections), std::end(interrsections), index) != std::end(interrsections))
                    reward+=100;
                else if(find(std::begin(sides), std::end(sides), index) != std::end(sides))
                    reward+=50;
                else
                    reward+=10;
            }

        }
        player = getHumanFieldstate();
        if(Game::getGameMap()->getBoardFields()[index].getPlayerID() == player)
        {
            // For each Human piece get a big negative reward which serves as counting number of pieces
            reward -= 10000;

            unsigned checkIndex1 = Game::getGameMap()-> getBoardFields()[index].getMills().first.first;
            unsigned checkIndex2 = Game::getGameMap()-> getBoardFields()[index].getMills().first.second;

            unsigned checkIndex3 = Game::getGameMap() -> getBoardFields()[index].getMills().second.first;
            unsigned checkIndex4 = Game::getGameMap() -> getBoardFields()[index].getMills().second.second;

            // Two other fields are empty, small rewards vary on the field position
            if (Game::getGameMap() -> getBoardFields()[checkIndex1].getPlayerID() == FIELDSTATE::EMPTY && Game::getGameMap() -> getBoardFields()[checkIndex2].getPlayerID() == FIELDSTATE::EMPTY)
            {
                if(find(std::begin(interrsections), std::end(interrsections), index) != std::end(interrsections))
                    reward-=10;
                else if(find(std::begin(sides), std::end(sides), index) != std::end(sides))
                    reward-=5;
                else
                    reward-=1;
            }

            if (Game::getGameMap() -> getBoardFields()[checkIndex3].getPlayerID() == FIELDSTATE::EMPTY && Game::getGameMap() -> getBoardFields()[checkIndex4].getPlayerID() == FIELDSTATE::EMPTY)
            {
                if(find(std::begin(interrsections), std::end(interrsections), index) != std::end(interrsections))
                    reward-=10;
                else if(find(std::begin(sides), std::end(sides), index) != std::end(sides))
                    reward-=5;
                else
                    reward-=1;
            }

            // One field is empty and other one is AIs, rewards vary on the field position,
            // bigger negative rewards here since after checking heuristic its Humans turn and if there are two of human pieces in same line it means he will mill next turn

            if ((Game::getGameMap() -> getBoardFields()[checkIndex1].getPlayerID() == FIELDSTATE::EMPTY && Game::getGameMap() -> getBoardFields()[checkIndex2].getPlayerID() == player) || \
                (Game::getGameMap() -> getBoardFields()[checkIndex1].getPlayerID() == player && Game::getGameMap() -> getBoardFields()[checkIndex2].getPlayerID() == FIELDSTATE::EMPTY) )
            {
                if(find(std::begin(interrsections), std::end(interrsections), index) != std::end(interrsections))
                    reward-=500;
                else if(find(std::begin(sides), std::end(sides), index) != std::end(sides))
                    reward-=250;
                else
                    reward-=50;
            }

            if ((Game::getGameMap() -> getBoardFields()[checkIndex3].getPlayerID() == FIELDSTATE::EMPTY && Game::getGameMap() -> getBoardFields()[checkIndex4].getPlayerID() == player) || \
                (Game::getGameMap() -> getBoardFields()[checkIndex3].getPlayerID() == player && Game::getGameMap() -> getBoardFields()[checkIndex4].getPlayerID() == FIELDSTATE::EMPTY) )
            {
                if(find(std::begin(interrsections), std::end(interrsections), index) != std::end(interrsections))
                    reward-=500;
                else if(find(std::begin(sides), std::end(sides), index) != std::end(sides))
                    reward-=250;
                else
                    reward-=50;
            }
        }
    }

    return reward;
}

std::pair<int,int> GameAI::maxSetup(int depth, int remainingPieces, int alfa, int beta)
{
    int maxValue = INT32_MIN;
    int move = -1;
    Player* player = getPlayerAI();

    // If Human made a mill, we check to see what will happen after that and try to negate his mill by making a mill ourselves
    if (Game::getMillOccured())
    {

        Game::setMillOccured(false);

        int retVal = -1;

        for(int field_num = 0; field_num < NUM_OF_FIELDS; field_num++)
        {
            if(isValidToRemove(field_num, getPlayerHuman(), 0))
            {
                Game::getGameMap() -> getBoardFields()[field_num].deoccupy();

                retVal = std::get<0>(maxSetup(depth, Game::getBoardPieces(), alfa, beta));

                if(retVal > maxValue )
                {
                    maxValue = retVal;
                    move = field_num;
                }

                Game::getGameMap() -> getBoardFields()[field_num].occupy(playerAI);

                if(maxValue >= beta)
                {
                    return std::make_pair(maxValue, -1);
                }

                if(maxValue > alfa)
                {
                    alfa = maxValue;
                }
            }
        }
        return std::make_pair(maxValue, move);
    }

    // End of phase 1 so we check rewards in phase 2
    if( remainingPieces== 0 )
    {
        std::tuple<int,int,int> retVal = minPlay(maxDepthPhase2, alfa, beta);
        return std::make_pair(std::get<0>(retVal), -1);
    }

    if (depth <= 0)
    {
        int rewardAI = heuristicSetup();
        return std::make_pair(rewardAI, -1);
    }

    for(int field_num = 0; field_num < NUM_OF_FIELDS; field_num++)
    {
        if(Game::getGameMap()->getBoardFields()[field_num].isOccupied())
            continue;

        this->makeSetupMoveAI(player, field_num);

        std::pair<int,int> ret_val= minSetup(depth-1, remainingPieces-1, alfa, beta);

        if(ret_val.first > maxValue )
        {
            maxValue = ret_val.first;
            move = field_num;
        }

        this->revertSetupMoveAI(player, field_num);

        if(maxValue >= beta)
        {
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
    Player* player = getPlayerHuman();

    // AI made a mill so we continue simulating game from here
    if (Game::getMillOccured())
    {

        Game::setMillOccured(false);

        int retVal = -1;

        for(int field_num = 0; field_num < NUM_OF_FIELDS; field_num++)
        {
            if(isValidToRemove(field_num, getPlayerAI(), 0))
            {
                Game::getGameMap() -> getBoardFields()[field_num].deoccupy();

                retVal = std::get<0>(minSetup(depth, Game::getBoardPieces(), alfa, beta));

                if(retVal < minValue )
                {
                    minValue = retVal;
                }

                Game::getGameMap() -> getBoardFields()[field_num].occupy(getHumanFieldstate());

                if(minValue <= alfa )
                {
                    return std::make_pair(minValue, -1);
                }

                if(minValue < beta)
                {
                    beta = minValue;
                }
            }
        }

        return std::make_pair(minValue, -1);
    }

    // End of phase 1 so we check rewards in phase 2
    if( remainingPieces== 0 )
    {
        std::tuple<int,int,int> retVal = minPlay(maxDepthPhase2, alfa, beta);
        return std::make_pair(std::get<0>(retVal), -1);
    }

    if( depth <= 0 )
    {
        int rewardAI = heuristicSetup();
        return std::make_pair(rewardAI, -1);
    }

    for(int field_num = 0; field_num < NUM_OF_FIELDS; field_num++)
    {
        if(Game::getGameMap()->getBoardFields()[field_num].isOccupied())
            continue;

        this->makeSetupMoveAI(player, field_num);

        std::pair<int,int> ret_val= maxSetup(depth-1, remainingPieces-1,alfa, beta);

        if(ret_val.first < minValue )
        {
            minValue = ret_val.first;
        }

        this->revertSetupMoveAI(player, field_num);

        if(minValue <= alfa)
        {
            return std::make_pair(minValue, -1);
        }

        if(minValue < beta)
        {
            beta = minValue;
        }
    }

    return std::make_pair(minValue, -1);
}



