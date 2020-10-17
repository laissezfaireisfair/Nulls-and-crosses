#include <cstdlib>
#include "Screen.h"

namespace nullsAndCrosses {
	void Screen::clear() {
		std::system("clear"); // For Unix
		//std::system("cls"); // For Windows
	}

	void Screen::draw_field(Field const & field) {
		unsigned int const fieldSize = field.get_size();
		clear();
		for (unsigned int i = 0; i < fieldSize; ++i) {
			for (unsigned int j = 0; j < fieldSize; ++j){
				std::cout << field.at(i, j) << " ";
			}
			std::cout << std::endl;
		}
	}
}