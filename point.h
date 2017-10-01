#pragma once

namespace nullsAndCrosses {
	 /// Класс для хранения точки
    class Point{
        int x, y;
    public:
		Point();
		Point(const int x1, const int y1);
		void set_x(const int x1);
		void set_y(const int y1);
		int get_x() const;
		int get_y() const;
    };
}
