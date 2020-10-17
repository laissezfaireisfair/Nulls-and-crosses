#include "Field.h"
using namespace std;

namespace nullsAndCrosses {
	char Field::get_cell(const int x, const int y) const {
		return field.at(y).at(x);
	}
	void Field::set_cell(const int x, const int y, const char newSymbol) {
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
	char Field::get_cell(const Point point) const {
		return get_cell(point.get_x(), point.get_y());
	}
	void Field::set_cell(const Point point, const char newSymbol) {
		set_cell(point.get_x(), point.get_y(), newSymbol);
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
	int Field::get_size() const {
		return size;
	}
	bool Field::is_coord_correct(const Point point) const {
		if (point.get_x() >= 0 && point.get_x()<size && point.get_y() >= 0 && point.get_y()<size)
			return true;
		return false;
	}
	char Field::get_empty_symbol() const {
		return emptyCell;
	}
}
