#pragma once
#include <string>
#include <list>

namespace nullsAndCrosses {
	/// Класс для хранения информации об игроке
	class Player {
		std::string name;
		char symbol;
	public:
		Player() {
			name = "Jonn Doe";
			symbol = 'x';
		}
		Player(std::string n, char sym) {
			name = n;
			symbol = sym;
		}
		std::string get_name() { return name; }
		char get_symbol() { return symbol; }
	};

	/// Класс операций со списком игроков
	class OperationsWithListOfPlayers {
	public:
		static bool is_name_contains(std::list<Player> players, std::string newName) {
			if (players.empty())
				return false;
			if (players.front().get_name() == newName)
				return true;
			players.pop_front();
			return is_name_contains(players, newName);
		}
		static bool is_symbol_contains(std::list<Player> players, char newSymbol) {
			if (players.empty())
				return false;
			if (players.front().get_symbol() == newSymbol)
				return true;
			players.pop_front();
			return is_symbol_contains(players, newSymbol);
		}
	};
}
