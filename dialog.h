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
		void initializeInfo();
        /// Перезапуск с очисткой поля и возможностью поменять информацию
		void restartGame();
		/// Функция для подсчёта пользовательских точек на одной диагонали
		int  countDio1WithPoint(const char player, const Point newPoint) const;
		/// И на другой
		int  countDio2WithPoint(const char player, const Point newPoint) const;
        /// Проверка, победит ли игрок после постановки новой точки
		bool isWinOrNo(const Point newPoint, const char playerSymbol) const;
		/// Проверка на ничью
		bool isDrawOrNo(const int num_steps, const int size) const;
		/// Обработка 1 хода игры (от 1 юзера)
		Point stepOfGame(Player playerNow);
        /// Продолжить игру (без инициализации)
		void continueGame();
    public:
        /// Начать игру (с инициализацией)
		void newGame();
    };
}
