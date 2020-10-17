#include "Player.h"

namespace nullsAndCrosses {
    Player::Player() : Player("Noname", '0') {}

    Player::Player(std::string const & name, char symbol) :
        m_name(name),
        m_symbol(symbol)
    {}

    std::string const & Player::get_name() {
        return m_name;
    }

    char const & Player::get_symbol() {
        return m_symbol;
    }
}