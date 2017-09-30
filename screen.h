#pragma once
#include <iostream>
#include <cstdlib>
#include <string>
#include "field.h"

namespace nullsAndCrosses {
	/// Класс для работы с выводом
	class Screen {
		static std::string getField(Field &field) {
			std::string str;
			for (int i = 0; i < field.getSize(); i++) {
				for (int j = 0; j < field.getSize(); j++) {
					str += field.getCell(Point(i, j));
					if (j < field.getSize() - 1)
						str += " ";
					else
						str += '\n';
				}
			}
			return str;
		}
	public:
		static void clear() {
			system("clear");
		}
		static void draw(Field &field) {
			clear();
			std::cout << getField(field);
		}

	};
}