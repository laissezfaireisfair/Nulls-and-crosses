#include "PlayerManager.h"

namespace nullsAndCrosses {
	PlayerManager::PlayerManager() {
		m_players = std::vector<std::shared_ptr<Player>>();
	}

	void add_player(Player const & player) {
		m_players.emplace_back(std::make_shared<Player>(player));
	}

    size_t get_number_of_players() const {
    	return m_players.size();
    }

    Player & player(size_t const position) {
    	return m_players.at(position);
    }

    Player const & player(size_t const position) const {
    	return m_players.at(position);
    }

    bool is_name_used(std::string const & name) const {
    	for (auto &player : m_players)
    		if (player->get_name() == name)
    			return false;
    	return true;
    }

    bool is_symbol_used(char symbol) const {
    	for (auto &player : m_players)
    		if (player->get_symbol() == symbol)
    			return false;
    	return true;
    }
}