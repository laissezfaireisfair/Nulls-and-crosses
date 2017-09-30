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
		std::string getName() { return name; }
		char getSymbol() { return symbol; }
	};

	/// Класс операций со списком игроков
	class OperationsWithListOfPlayers {
	public:
		static bool isNameContain(std::list<Player> players, std::string newName) {
			if (players.empty())
				return false;
			if (players.front().getName() == newName)
				return true;
			players.pop_front();
			return isNameContain(players, newName);
		}
		static bool isSymbolContain(std::list<Player> players, char newSymbol) {
			if (players.empty())
				return false;
			if (players.front().getSymbol() == newSymbol)
				return true;
			players.pop_front();
			return isSymbolContain(players, newSymbol);
		}
	};
}