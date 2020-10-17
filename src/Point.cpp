#include "Point.h"

namespace nullsAndCrosses {
	Point::Point() :
		m_x(0),
		m_y(0)
	{}

	Point::Point(int const x, int const y) :
		m_x(x),
		m_y(y)
	{}

	int const & Point::x() const {
		return m_x;
	}

    int const & Point::y() const {
    	return m_y;
    }

    void Point::set_x(int const x) {
    	m_x = x;
    }

    void Point::set_y(int const y) {
    	m_y = y;
    }
}