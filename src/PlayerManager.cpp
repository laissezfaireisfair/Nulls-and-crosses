#include "PlayerManager.h"

namespace nullsAndCrosses {
	PlayerManager::PlayerManager() {
		m_players = std::vector<std::shared_ptr<Player>>();
        m_winnerSet = false;
        m_winnerPosition = 0;
	}

	void PlayerManager::add_player(Player const & player) {
		m_players.emplace_back(std::make_shared<Player>(player));
	}

    size_t PlayerManager::get_number_of_players() const {
    	return m_players.size();
    }

    Player & PlayerManager::player(size_t const position) {
    	return m_players.at(position);
    }

    Player const & PlayerManager::player(size_t const position) const {
    	return m_players.at(position);
    }

    bool PlayerManager::is_name_used(std::string const & name) const {
    	for (auto &player : m_players)
    		if (player->get_name() == name)
    			return false;
    	return true;
    }

    bool PlayerManager::is_symbol_used(char const symbol) const {
    	for (auto &player : m_players)
    		if (player->get_symbol() == symbol)
    			return false;
    	return true;
    }

    void PlayerManager::set_winner(size_t const position) {
        m_winnerSet = true;
        m_winnerPosition = position;
    }

    void PlayerManager::drop_winner() {
        m_winnerSet = false;
        m_winnerPosition = 0;
    }

    bool PlayerManager::is_winner_exist() const {
        return m_winnerSet;
    }

    Player & PlayerManager::winner() {
        if (!m_winnerSet)
            throw std::logic_error("Try to get unexisting winner.");
        return player(m_winnerPosition);
    }
    Player const & PlayerManager::winner() const {
        if (!m_winnerSet)
            throw std::logic_error("Try to get unexisting winner.");
        return player(m_winnerPosition);
    }
}