#pragma once
#include <string>

namespace nullsAndCrosses {
	class Player {
	public:
        Player();
		Player(std::string const & name, char symbol);
		std::string const & get_name();
		char const & get_symbol();
	private:
		std::string const m_name;
		char const m_symbol;
	};
}
