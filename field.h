#pragma once
#include "point.h"
#include <vector>

namespace nullsAndCrosses { // TODO: Rewrite this with lists or vectors
	/// Класс для работы с полем
	class Field {
		std::vector<std::vector<char>> field;
		char emptyCell;
		int size;
		char get_cell(const int x, const int y) const;
		void set_cell(const int x, const int y, const char newSymbol);
	public:
		Field();
		Field(const char symbol, const int s);
		~Field();
		void clear();
		char get_cell(const Point point) const;
		void set_cell(const Point point, const char newSymbol);
		void initialize(const char symbol, const int s);
		int get_size() const;
		bool is_coord_correct(const Point point) const;
		char get_empty_symbol() const;
	};
}
