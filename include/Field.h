#pragma once
#include <vector>
#include "Point.h"

namespace nullsAndCrosses {
	class Field {
	public:
		Field(char emptyCellSymbol, unsigned int size);
		void clear();
		char & at(Point const & place);
		char const & at(Point const & place) const;
		unsigned int const & get_size() const;
	private:
		std::vector<std::vector<char>> m_field;
		char const m_emptyCellSymbol;
		unsigned int const m_size;
	};
}
