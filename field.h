#pragma once
#include "point.h"
#include <vector>

namespace nullsAndCrosses {
	/// Класс для работы с полем
	class Field {
		std::vector<std::vector<char>> field;
		char emptyCell;
		int size;
		char get_cell(const int xCoord, const int yCoord) const;
		void set_cell(const int xCoord, const int yCoord, const char newSymbol);
	public:
		Field();
		Field(const char emptyCellSymbol, const int fieldSize);
		~Field();
		void clear();
		char get_cell(const Point coords) const;
		void set_cell(const Point coords, const char newSymbol);
		void initialize(const char emptyCellSymbol, const int fieldSize);
		int get_size() const;
		bool is_coords_correct(const Point coords) const;
		char get_empty_symbol() const;
	};
}
