#include "humanplayer.h"

HumanPlayer::HumanPlayer (VALUE playerID)
    : m_id(playerID)
{
}

void HumanPlayer::changeTurn()
{
    m_turn = !m_turn;
}

bool HumanPlayer::turn() const
{
    return m_turn;
}

VALUE HumanPlayer::id() const
{
    return m_id;
}
