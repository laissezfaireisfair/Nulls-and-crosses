#include "Point.h"
namespace nullsAndCrosses {
	Point::Point() {
		x = y = 0;
	}
	Point::Point(const int x1, const int y1) {
		x = x1;
		y = y1;
	}
	void Point::set_x(const int x1) {
		x = x1;
	}
	void Point::set_y(const int y1) {
		y = y1;
	}
	int Point::get_x() const {
		return x;
	}
	int Point::get_y() const {
		return y;
	}
}