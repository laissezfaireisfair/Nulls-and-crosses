#pragma once
#include <vector>
#include "Point.h"

namespace nullsAndCrosses {
	class Field {
	public:
		Field(char emptyCellSymbol, unsigned int fieldSize);
		void clear();
		char & at(Point const & place);
		char const & at(Point const & place) const;
		unsigned int const & get_size() const;
	private:
		std::vector<std::vector<char>> field;
		char const emptyCellSymbol;
		unsigned int const size;
	};
}
