#pragma once
#include <iostream>
#include <cstdlib>
#include <string>
#include "Field.h"

namespace nullsAndCrosses {
	/// Класс для работы с выводом
	class Screen {
		static std::string get_field(Field &field) {
			std::string str;
			for (int i = 0; i < field.get_size(); i++) {
				for (int j = 0; j < field.get_size(); j++) {
					str += field.get_cell(Point(j, i));
					if (j < field.get_size() - 1)
						str += " ";
					else
						str += '\n';
				}
			}
			return str;
		}
	public:
		static void clear() {
			//system("clear"); // For Linux
			system("cls"); // For Windows
		}
		static void draw(Field &field) {
			clear();
			std::cout << get_field(field);
		}

	};
}
