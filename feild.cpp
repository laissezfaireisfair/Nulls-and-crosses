#include "field.h"

namespace nullsAndCrosses {
	char Field::getCell(const int x, const int y) const {
		return field[size - y - 1][size - x - 1]; // TODO: exceptions handling
	}
	void Field::setCell(const int x, const int y, const char newSymbol) {
		field[size - y - 1][size - x - 1] = newSymbol; // TODO: exceptions handling
	}
	Field::Field() {
		field = nullptr;
		emptyCell = 0;
		size = 0;
	}
	Field::Field(const char symbol, const int s) {
		size = s;
		emptyCell = symbol;
		field = new char *[size];
		for (int i = 0; i < size; i++) {
			field[i] = new char[size];
			for (int j = 0; j < size; j++)
				field[i][j] = emptyCell;
		}
	}
	Field::~Field() {
		for (int i = 0; i<size; i++)
			delete field[i];
		delete field;
	}
	void Field::clear() {
		for (int i = 0; i < size; i++)
			for (int j = 0; j < size; j++)
				field[i][j] = emptyCell;
	}
	char Field::getCell(const Point point) const {
		return getCell(point.getX(), point.getY());
	}
	void Field::setCell(const Point point, const char newSymbol) {
		setCell(point.getX(), point.getY(), newSymbol);
	}
	void Field::initialize(const char symbol, const int s) {
		//if(Field!=nullptr) TODO: test it
		//    throw string("Field::initialize. Error. It has been initialized.");
		size = s;
		emptyCell = symbol;
		field = new char *[size];
		for (int i = 0; i < size; i++) {
			field[i] = new char[size];
			for (int j = 0; j < size; j++)
				field[i][j] = emptyCell;
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
