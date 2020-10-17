#include "Field.h"
using namespace std;

namespace nullsAndCrosses {
	Field::Field(char const emptyCellSymbol, unsigned int const size) :
		m_emptyCellSymbol(emptyCellSymbol),
		m_size(size)
	{
		m_field = std::vector<std::vector<char>>(m_size, std::vector<char>(m_size, emptyCellSymbol));
	}

	void Field::clear() {
		for (auto &str : m_field)
			for (auto &cell: str)
				cell = emptyCellSymbol;
	}

	char & Field::at(Point const & place) {
		return m_field.at(place.y()).at(place.x());
	}

	char const & Field::at(Point const & place) const {
		return m_field.at(place.y()).at(place.x());
	}

	unsigned int const & Field::get_size() const {
		return m_size;
	}
}
