#include "game.h"

namespace nullsAndCrosses {
	/// Инициализация информации об игре
	void Game::initialize_info() {
		players = Dialog::ask_players_info();
		sizeWinCombo = Dialog::ask_win_combo_size();
	}
	/// Перезапуск с очисткой поля и возможностью поменять информацию
	void Game::restart_game() {
		field.clear();
		if (Dialog::ask_changing_info()) {
			initialize_info();
			field.clear();
			field.initialize(Dialog::ask_empty_cell_symbol(players), Dialog::ask_field_size());
		}
		continue_game();
	}
	/// Функция для подсчёта пользовательских точек на одной диагонали
	int  Game::count_dio_1_with_point(const char player, const Point newPoint) const {
		int maxCombo = 0, beginCoordX, beginCoordY, dioLen, size = field.get_size();
		int nowCombo = 0;
		if (newPoint.get_x() > newPoint.get_y()) {
			beginCoordX = newPoint.get_x() - newPoint.get_y();
			beginCoordY = 0;
			dioLen = size - beginCoordX;
		}
		else {
			beginCoordX = 0;
			beginCoordY = newPoint.get_y() - newPoint.get_x();
			dioLen = size - beginCoordY;
		}
		for (int i = 0; i < dioLen; i++) {
			if (field.get_cell(Point(beginCoordX + i, beginCoordY + i)) == player)
				nowCombo++;
			else {
				maxCombo = (nowCombo > maxCombo) ? nowCombo : maxCombo;
				nowCombo = 0;
			}
		}
		return (nowCombo > maxCombo) ? nowCombo : maxCombo;
	}
	/// И на другой
	int  Game::count_dio_2_with_point(const char player, const Point newPoint) const {
		int maxCombo = 0, nowCombo = 0, xBegin, yBegin, len, size = field.get_size();
		if (newPoint.get_x() + newPoint.get_y() <= size - 1) {
			xBegin = 0;
			yBegin = newPoint.get_x() + newPoint.get_y();
			len = yBegin + 1;
		}
		else {
			xBegin = newPoint.get_x() + newPoint.get_y() - size + 1;
			yBegin = size - 1;
			len = size - xBegin;
		}
		for (int i = 0; i < len; i++) {
			if (field.get_cell(Point(xBegin + i, yBegin - i)) == player)
				nowCombo++;
			else {
				maxCombo = (nowCombo > maxCombo) ? nowCombo : maxCombo;
				nowCombo = 0;
			}
		}
		return (nowCombo > maxCombo) ? nowCombo : maxCombo;
	}
	/// Проверка, победит ли игрок после постановки новой точки 
	bool Game::is_win_or_no(const Point newPoint, const char playerSymbol) const {
		int size = field.get_size(), counter1 = 0, counter2 = 0;
		for (int i = 0; i < size; i++) { // Перебор строки и столбца с новой точкой
			if (field.get_cell(Point(newPoint.get_x(), i)) == playerSymbol) {
				counter1++;
				if (counter1 >= sizeWinCombo)
					return true;
			}
			else
				counter1 = 0;
			if (field.get_cell(Point(i, newPoint.get_y())) == playerSymbol) {
				counter2++;
				if (counter2 >= sizeWinCombo)
					return true;
			}
			else
				counter2 = 0;
		}
		counter1 = counter2 = 0;
		if (count_dio_1_with_point(playerSymbol, newPoint) >= sizeWinCombo)
			return true;
		if (count_dio_2_with_point(playerSymbol, newPoint) >= sizeWinCombo)
			return true;
		return false;
	}
	/// Проверка на ничью
	bool Game::is_draw_or_no(const int num_steps, const int size) const {
		return num_steps < size*size;
	}
	/// Обработка 1 хода игры (от 1 юзера)
	Point Game::step_of_game(Player playerNow) {
		Point newPoint;
		newPoint = Dialog::ask_new_symbol_coord(playerNow.get_name());
		if (!field.is_coord_correct(newPoint)) {
			cout << "Wrong input. There are no cell with this coords." << endl;
			return step_of_game(playerNow);
		}
		if (field.get_cell(newPoint) != field.get_empty_symbol()) {
			cout << "Wrong input. This cell is already used." << endl;
			return step_of_game(playerNow);
			
		}
		field.set_cell(newPoint, playerNow.get_symbol());
		return newPoint;
	}
	/// Продолжить игру (без инициализации)
	void Game::continue_game() {
		Point newPoint;
		Player playerNow;
		int stepCounter = 0; // Для опеределения ничьей
		do {
			Screen::draw(field);
			playerNow = players.front();
			newPoint = step_of_game(playerNow);
			stepCounter++;
			players.pop_front();
			players.push_back(playerNow);
		} while (!is_win_or_no(newPoint, playerNow.get_symbol()) || !is_draw_or_no(stepCounter, field.get_size()));
		Dialog::print_final_results(field, playerNow.get_name(), !is_win_or_no(newPoint, playerNow.get_symbol()));
		if (Dialog::ask_start_new_or_no())
			restart_game();
	}
	/// Начать игру (с инициализацией)
	void Game::new_game() {
		initialize_info();
		field.initialize(Dialog::ask_empty_cell_symbol(players), Dialog::ask_field_size());
		continue_game();
	}
}
