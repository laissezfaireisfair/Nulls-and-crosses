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
			m_playerManager.add_player(Dialog::ask_player_info());
		} while (Dialog::ask_player_if_want_to_add_new());
	}

	void Game::init_game_info() {
		unsigned int fieldSize = ask
	}
}