#include "Game.h"
#include "Player.h"
#include "Point.h"
#include "Screen.h"
#include "Dialog.h"

namespace nullsAndCrosses {
	Game::Game() {
		m_status = NOT_STARTED;
		init_player_info();
	}

	void Game::run() {
		init_game_info();
		m_status = RUNNING;
		while (m_status == RUNNING) {
			step();
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

	void step() {
		unsigned int const playersNum = m_playerManager.get_number_of_players();
		for (unsigned int i = 0; i < playersNum; ++i) {
			Player & playerNow = m_playerManager.player[i];
			bool suitableStepGetted = false;
			Point newStep;
			do {
				newStep = Dialog::ask_new_step_position();
				if (m_field.at(newStep) == m_field)
					suitableStepGetted = true;
			} while (!suitableStepGetted);
			m_field.at(newStep) = playerNow.get_symbol();
			win_and_draw_check();
			if (m_status != RUNNING)
				return;
		}
	}
}