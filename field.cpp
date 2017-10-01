#include "field.h"
using namespace std;

namespace nullsAndCrosses {
	char Field::getCell(const int x, const int y) const {
		return field.at(y).at(x);
	}
	void Field::setCell(const int x, const int y, const char newSymbol) {
		field.at(y).at(x) = newSymbol;
	}
	Field::Field() {
		field = vector<vector<char>>();
		emptyCell = 0;
		size = 0;
	}
	Field::Field(const char symbol, const int s) {
		initialize(symbol, s);
	}
	Field::~Field() {
		field.clear();
	}
	void Field::clear() {
		for (int i = 0; i < size; i++)
			for (int j = 0; j < size; j++)
				field.at(i).at(j) = emptyCell;
	}
	char Field::getCell(const Point point) const {
		return getCell(point.getX(), point.getY());
	}
	void Field::setCell(const Point point, const char newSymbol) {
		setCell(point.getX(), point.getY(), newSymbol);
	}
	void Field::initialize(const char symbol, const int s) {
		size = s;
		emptyCell = symbol;
		field = vector<vector<char>>();
		for (int i = 0; i < size; i++) {
			field.push_back(vector<char>());
			for (int j = 0; j < size; j++)
				field.at(i).push_back(emptyCell);
		}
	}
	int Field::getSize() const {
		return size;
	}
	bool Field::isCoordCorrect(const Point point) const {
		if (point.getX() >= 0 && point.getX()<size && point.getY() >= 0 && point.getY()<size)
			return true;
		return false;
	}
	char Field::getEmptySymbol() const {
		return emptyCell;
	}
}
