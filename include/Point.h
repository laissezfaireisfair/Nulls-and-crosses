#pragma once

namespace nullsAndCrosses {
    class Point{
    public:
		Point();
		Point(int x, int y);
		int const & x() const;
        int const & y() const;
        void set_x(int x);
        void set_y(int y);
    private:
        int m_x, m_y;
    };
}
