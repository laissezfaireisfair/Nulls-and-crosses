#pragma once
#include <string>
#include <iostream>
#include "Player.h"
#include "Point.h"

namespace nullsAndCrosses {
	/// Asking functions asks again in case of wrong input
	class Dialog {
	public:
		static Player ask_player_info();
		static bool ask_player_if_want_to_add_new();
		static bool ask_if_start_new_game();
		static Point ask_new_step_position();
		static unsigned int ask_field_size();
		static void warn_field_too_large();
		static unsigned int ask_win_length_size();
		static char ask_empty_cell_symbol();
		static bool ask_if_change_preferences();
		static void print_draw_message();
		static void print_winner(std::string const & name);
	private:
		static bool ask_yes_or_no();
		static std::string ask_players_name();
		static char ask_players_personal_symbol();
	};
}
