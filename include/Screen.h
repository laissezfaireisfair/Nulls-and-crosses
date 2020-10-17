#pragma once
#include "Field.h"

namespace nullsAndCrosses {
	class Screen {
	public:
		static void clear();
		static void draw_field(Field const & field);
	};
}
