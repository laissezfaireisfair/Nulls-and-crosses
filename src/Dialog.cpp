#include <iostream>
#include "Dialog.h"

namespace nullsAndCrosses {
	Player Dialog::ask_player_info() {
		return Player(ask_players_name(), ask_players_personal_symbol());
	}

	bool Dialog::ask_player_if_want_to_add_new() {
		std::cout << "Do you want to add another player? ";
		return ask_yes_or_no();
	}

	bool Dialog::ask_if_start_new_game() {
		std::cout << "Do you want to start new game? ";
		return ask_yes_or_no();
	}

	Point Dialog::ask_new_step_position(Player const & player) {
		std::cout << player.get_name() << ", your turn. ";
		std::cout << "Type your next symbol position (x y):" << std::endl;
		unsigned int x, y;
		if (std::cin >> x && std::cin >> y)
			return Point(x, y);
		std::cout << "Wrong input. Try again." << std::endl;
		return ask_new_step_position();
	}

	unsigned int Dialog::ask_field_size() {
		std::cout << "How large should be field?" << std::endl;
		unsigned int size;
		if (std::cin >> size)
			return size;
		std::cout << "Wrong input. Try again." << std::endl;
		return ask_field_size();
	}

	void Dialog::warn_field_too_large(unsigned int const sizeLimit) {
		std::cout << "Warning: Size is larger than recomended limit. Limit is ";
		std::cout << sizeLimit << std::endl;
	}

	unsigned int Dialog::ask_win_length_size() {
		std::cout << "How large should be winning combo?" << std::endl;
		unsigned int winLength;
		if (std::cin >> winLength)
			return winLength;
		std::cout << "Wrong input. Try again." << std::endl;
		return ask_win_length_size();
	}

	char Dialog::ask_empty_cell_symbol() {
		std::cout << "Type your personal symbol." << std::endl;
		char name;
		if (std::cin >> name)
			return name;
		std::cout << "Wrong input. Try again." << std::endl;
		return ask_players_personal_symbol();
	}

	bool Dialog::ask_if_change_preferences() {
		std::cout << "Do you want to change preferences? ";
		return ask_yes_or_no();
	}

	void Dialog::print_draw_message() {
		std::cout << "Draw." << std::endl;
	}

	void Dialog::print_winner(std::string const & name) {
		std::cout << name << "is winner!" << std::endl;
	}

	bool Dialog::ask_yes_or_no() {
		std::cout << "(y/n)" << endl;
		std::string input;
		std::cin >> input;
		if (input.length() != 1 || input[0] != 'y' || input[0] != 'n') {
			std::cout << "Wrong input. You should print y or n. Try again." << std::endl;
			return ask_yes_or_no();
		}
		return input[0] == 'y';
	}

	std::string Dialog::ask_players_name() {
		std::cout << "Type your name." << std::endl;
		std::string name;
		if (std::cin >> name)
			return name;
		std::cout << "Wrong input. Try again." << std::endl;
		return ask_players_name();
	}

	char Dialog::ask_players_personal_symbol() {
		std::cout << "Type your personal symbol." << std::endl;
		char name;
		if (std::cin >> name)
			return name;
		std::cout << "Wrong input. Try again." << std::endl;
		return ask_players_personal_symbol();
	}

}