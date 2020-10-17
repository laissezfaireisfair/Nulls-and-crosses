#pragma once
#include <memory>
#include <vector>
#include <string>
#include "Player.h"

namespace nullAndCrosses{
    class PlayerManager {
    public:
        PlayerManager();
        void add_player(Player const & player);
        size_t get_number_of_players() const;
        Player & player(size_t position);
        Player const & player(size_t position) const;
        bool is_name_used(std::string const & name) const;
        bool is_symbol_used(char symbol) const;
        ~PlayerManager();
    private:
        vector<std::shared_ptr<Player>> m_players;
    };
}