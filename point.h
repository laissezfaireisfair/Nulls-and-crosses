#pragma once

namespace nullsAndCrosses {
	 /// ����� ��� �������� �����
    class Point{
        int x, y;
    public:
		Point();
		Point(const int x1, const int y1);
		void setX(const int x1);
		void setY(const int y1);
		int getX() const;
		int getY() const;
    };
}