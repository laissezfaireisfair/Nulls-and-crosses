#pragma once
#include <iostream>
#include <cstdlib>
#include <string>
#include "Field.h"

namespace nullsAndCrosses {
	class Screen {
	public:
		static void clear();
		static void draw_field(Field const & field);
	};
}
