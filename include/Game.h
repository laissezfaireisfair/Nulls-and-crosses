#pragma once
#include "Field.h"
#include "PlayerManager.h"


namespace nullsAndCrosses {
    class Game {
    public:
        Game();
		void run();
    private:
        enum class GameStatus {NOT_STARTED, RUNNING, DRAW, WIN};
        Field m_field;
        unsigned int m_winLength;
        PlayerManager m_playerManager;
        GameStatus m_status;
        void init_player_info(); // Field and win length
        void init_game_info();
        void step();
        void win_and_draw_check();
        void end();
        static unsigned int get_recomended_size_limit();
    };
}
