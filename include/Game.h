#pragma once
#include "Field.h"
#include "Dialog.h"
#include "Screen.h"
#include "Player.h"
#include "PlayerManager.h"


namespace nullsAndCrosses {
    class Game {
    public:
        Game();
		void run();
    private:
        enum class GameStatus {NOt_STARTED, RUNNING, DRAW, WIN};
        Field m_field;
        PlayerManager m_playerManager;
        GameStatus m_status;
        void new_game_without_init();
        void new_game_with_init();
        void step();
        void end();
    };
}
