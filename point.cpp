#include "point.h"
namespace nullsAndCrosses {
	Point::Point() {
		x = y = 0;
	}
	Point::Point(const int x1, const int y1) {
		x = x1;
		y = y1;
	}
	void Point::setX(const int x1) {
		x = x1;
	}
	void Point::setY(const int y1) {
		y = y1;
	}
	int Point::getX() const {
		return x;
	}
	int Point::getY() const {
		return y;
	}
}