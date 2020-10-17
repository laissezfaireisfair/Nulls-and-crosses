#pragma once
#include <string>

namespace nullsAndCrosses {
	class Player {
	public:
        Player();
		Player(std::string const & name, char symbol);
		std::string const & get_name();
		char get_symbol();
	private:
		std::string m_name;
		char m_symbol;
	};
}
