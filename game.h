#pragma once
#include <string>
#include <iostream>
#include <list>
#include "field.h"
#include "dialog.h"
#include "players.h"

using namespace std;

namespace nullsAndCrosses {
	 /// Класс обработки игры
    class Game {
        list<Player> (players);
        Field field;
        int sizeWinCombo;
        /// Инициализация информации об игре
		void initialize_info();
        /// Перезапуск с очисткой поля и возможностью поменять информацию
		void restart_game();
		/// Функция для подсчёта пользовательских точек на одной диагонали
		int  count_dio_1_with_point(const char playerSymbol, const Point newPoint) const;
		/// И на другой
		int  count_dio_2_with_point(const char playerSymbol, const Point newPoint) const;
        /// Проверка, победит ли игрок после постановки новой точки
		bool is_win_or_no(const Point newPoint, const char playerSymbol) const;
		/// Проверка на ничью
		bool is_draw_or_no(const int num_steps, const int fieldSize) const;
		/// Обработка 1 хода игры (от 1 юзера)
		Point step_of_game(Player playerNow);
        /// Продолжить игру (без инициализации)
		void continue_game();
    public:
        /// Начать игру (с инициализацией)
		void new_game();
    };
}
