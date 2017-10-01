#pragma once

namespace nullsAndCrosses {
	 /// Класс для хранения точки
    class Point{
        int x, y;
    public:
		Point();
		Point(const int xCoord, const int yCoord);
		void set_x(const int xCoord);
		void set_y(const int yCoord);
		int get_x() const;
		int get_y() const;
    };
}
