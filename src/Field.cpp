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
		if (place.x() > m_size || place.y() > m_size)
			throw std::out_of_range("No such cell in the field");
		return m_field[place.y()][place.x()]
	}

	char const & Field::at(Point const & place) const {
		if (place.x() > m_size || place.y() > m_size)
			throw std::out_of_range("No such cell in the field");
		return m_field[place.y()][place.x()]
	}

	unsigned int const & Field::get_size() const {
		return m_size;
	}
}
