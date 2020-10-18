#include "Game.h"
#include "Player.h"
#include "Point.h"
#include "Screen.h"
#include "Dialog.h"

namespace nullsAndCrosses {
	Game::Game() {
		m_status = NOT_STARTED;
		init_player_info();
		init_game_info();
	}

	void Game::run() {
		m_status = RUNNING;
		m_stepCounter = 0;
		while (m_status == RUNNING) {
			step();
			++m_stepCounter;
		}
		end();
	}

	void Game::init_player_info() {
		m_playerManager = PlayerManager();
		do {
			bool suitableInfoGetted = false;
			Player newPlayer = Player();
			do {
				newPlayer = Dialog::ask_player_info();
				if (m_playerManager.is_name_used(newPlayer.get_name())) {
					Dialog::warn_name_already_used();
					continue;
				}
				if (m_playerManager.is_symbol_used(newPlayer.get_symbol())) {
					Dialog::warn_symbol_already_used();
					continue;
				}
				suitableInfoGetted = true;
			} while (!suitableInfoGetted);
			m_playerManager.add_player(Dialog::ask_player_info());
		} while (Dialog::ask_player_if_want_to_add_new());
	}

	void Game::init_game_info() {
		unsigned int const fieldSize = ask_field_size();
		if (fieldSize > get_recomended_size_limit()) {
			Dialog::warn_field_too_large();
			if(ask_if_change_preferences())
				init_game_info();
		}
		bool suitableInfoGetted = false;
		char emptyCellSymbol;
		do {
			emptyCellSymbol = ask_empty_cell_symbol();
			if (!m_playerManager.is_symbol_used(emptyCellSymbol))
				suitableInfoGetted = true;
		} while (!suitableInfoGetted);
		m_field = Field(emptyCellSymbol, fieldSize);
		m_winLength = ask_win_length();
	}

	void Game::step() {
		unsigned int const playersNum = m_playerManager.get_number_of_players();
		for (unsigned int i = 0; i < playersNum; ++i) {
			Player & playerNow = m_playerManager.player[i];
			bool suitableStepGetted = false;
			Point newStep;
			do {
				newStep = Dialog::ask_new_step_position();
				if (newStep.x() < m_field.get_size() && newStep.y() < m_field.get_size())
					if (m_field.at(newStep) == m_field)
						suitableStepGetted = true;
			} while (!suitableStepGetted);
			m_field.at(newStep) = playerNow.get_symbol();
			win_and_draw_check(playerNow, newStep);
			if (m_status != RUNNING)
				return;
		}
	}
	void Game::end() {
		if (m_status == WIN)
			Dialog::print_winner(m_playerManager.winner());
		if (m_status == DRAW)
			Dialog::print_draw_message();
		if (ask_if_start_new_game()) {
			m_status = NOT_STARTED;
			if (Dialog::ask_if_change_preferences()) {
				init_player_info();
				init_game_info();
			} else {
				m_field.clear();
			}
			run();
		}
	}

	unsigned int get_recomended_size_limit() {
		unsigned int const recomendedSizeLimit = 10;
		return recomendedSizeLimit;
	}

	void win_and_draw_check(Player const & player, Point const & lastStep) {
		if (count_players_combo_on_string(player, lastStep) >= m_winLength) {
			m_status = WIN;
			m_playerManager.set_winner(player);
			return;
		}
		if (count_players_combo_on_column(player, lastStep) >= m_winLength) {
			m_status = WIN;
			m_playerManager.set_winner(player);
			return;
		}
		if (count_players_combo_on_diag1(player, lastStep) >= m_winLength) {
			m_status = WIN;
			m_playerManager.set_winner(player);
			return;
		}
		if (count_players_combo_on_diag2(player, lastStep) >= m_winLength) {
			m_status = WIN;
			m_playerManager.set_winner(player);
			return;
		}
		unsigned int const numberOfCells = m_field.get_size() * m_field.get_size();
		if (m_stepCounter == numberOfCells)
			m_status = DRAW;
	}

	unsigned int count_players_combo_on_string(Player const & player, Point const & place) const {
		size_t const fieldSize = m_field.get_size();
		unsigned int const strNum = place.y();
		unsigned int comboCounter = 0;
		for (unsigned int i = place.x(); i < fieldSize; ++i) {
			if (m_field.at(Point(i, strNum)) == player.get_symbol()) {
				++comboCounter;
			} else {
				break;
			}
		}
		for (unsigned int i = 1; i <= place.x(); ++i) {
			if (m_field.at(Point(place.x() - i, strNum)) == player.get_symbol()) {
				++comboCounter;
			} else {
				break;
			}
		}
		return comboCounter;
	}

    unsigned int count_players_combo_on_column(Player const & player, Point const & place) const {
    	size_t const fieldSize = m_field.get_size();
		unsigned int const colNum = place.x();
		unsigned int comboCounter = 0;
		for (unsigned int i = place.y(); i < fieldSize; ++i) {
			if (m_field.at(Point(colNum, i)) == player.get_symbol()) {
				++comboCounter;
			} else {
				break;
			}
		}
		for (unsigned int i = 1; i <= place.y(); ++i) {
			if (m_field.at(Point(colNum, place.y() - i)) == player.get_symbol()) {
				++comboCounter;
			} else {
				break;
			}
		}
		return comboCounter;
    }

    unsigned int count_players_combo_on_diag1(Player const & player, Point const & place) const {

    }

    unsigned int count_players_combo_on_diag2(Player const & player, Point const & place) const;

}