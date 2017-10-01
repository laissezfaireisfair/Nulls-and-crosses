#pragma once
#include "point.h"
#include <vector>

namespace nullsAndCrosses { // TODO: Rewrite this with lists or vectors
	/// Класс для работы с полем
	class Field {
		std::vector<std::vector<char>> field;
		char emptyCell;
		int size;
		char getCell(const int x, const int y) const;
		void setCell(const int x, const int y, const char newSymbol);
	public:
		Field();
		Field(const char symbol, const int s);
		~Field();
		void clear();
		char getCell(const Point point) const;
		void setCell(const Point point, const char newSymbol);
		void initialize(const char symbol, const int s);
		int getSize() const;
		bool isCoordCorrect(const Point point) const;
		char getEmptySymbol() const;
	};
}
