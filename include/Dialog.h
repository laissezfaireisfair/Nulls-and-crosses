#pragma once
#include <string>
#include <iostream>
#include <list>
#include "Player.h"
#include "Point.h"
#include "Screen.h"
using namespace std;

namespace nullsAndCrosses {
	/// Класс взаимодействия с пользователем
	class Dialog {
		static bool yn_handling() {
			string yn_in;
			bool yn_out;
			cout << "(y/n)" << endl;
			cin >> yn_in;
			if (!string_to_bool(yn_in, yn_out)) {
				cout << "Wrong input. You should print y or n. Try again." << endl;
				return yn_handling();
			}
			return yn_out;
		}
		/// Возвращает статус операции
		static char string_to_char(const string in, errorStatus &status) {
			status = noError;
			if (in.length() > 1)
				status = warning;
			return char(in.at(0));
		}
		/// Возвращает статус операции
		static int string_to_int(string in, errorStatus &status) {
			int out = 0;
			status = noError;
			for (unsigned int i = 0; i < in.length(); i++) {
				if (in.at(i) > '9' || in.at(i) < '0') {
					status = fatalError;
					return -1;
				}
				out *= 10;
				out += in.at(i) - '0';
			}
			return out;
		}
		/// Возвращает статус операции
		static bool string_to_bool(string in, errorStatus &status) {
			errorStatus = noError;
			if (in.length() > 1)
				errorStatus = warning;
			if (in.at(0) == 'y')
				return true;
			if (in.at(0) == 'n')
				return false;
			errorStatus = fatalError;
			return false;
		}
		static string ask_players_name() {
			string name;
			cout << "Print your name." << endl;
			cin >> name;
			return name;
		}
		static char ask_players_symbol() {
			string symbol;
			char symbolC;
			cout << "Print your symbol." << endl;
			cin >> symbol;
			if (!(string_to_char(symbol, symbolC))) {
				cout << "Wrong input. You should print symbol." << endl;
				return ask_players_symbol();
			}
			return symbolC;
		}
		static bool ask_players_if_want_add_new() {
			cout << "Would you like to add more players?" << endl;
			return yn_handling();
		}
		static void player_wins(string name, bool noOne) {
			if (noOne) {
				cout << "Draw!" << endl;
				return;
			}
			cout << name << " wins!" << endl;
		}
	public:
		/// Запрос информации об игроках
		static list <Player> ask_players_info() {
			Screen::clear();
			list <Player>(players);
			string name;
			char symbol;
			do {
				do {
					name = ask_players_name();
				} while (OperationsWithListOfPlayers::is_name_contains(players, name));
				do {
					symbol = ask_players_symbol();
				} while (OperationsWithListOfPlayers::is_symbol_contains(players, symbol));
				players.push_back(Player(name, symbol));
			} while (ask_players_if_want_add_new());
			return players;
		}
		/// Спросить хотят ли начать новую игру
		static bool ask_start_new_or_no() {
			cout << "Would you like to start new game?" << endl;
			return yn_handling();
		}
		/// Отрисовать поле и запросить координаты нового символа
		static Point ask_new_symbol_coord(string name) {
			// Не очищаем экран, чтобы не стереть отображение поля
			string x_in, y_in;
			int x_out, y_out;
			cout << name << ", where do you prefer to put symbol? (x, y)" << endl;
			cin >> x_in >> y_in;
			if (!string_to_int(x_in, x_out) || !string_to_int(y_in, y_out)) {
				cout << "Wrong input. You should print coords of new point. Try again" << endl;
				return ask_new_symbol_coord(name);
			}
			x_out--; // Пользователь нумерует с единицы, а мы с нуля
			y_out--;
			return Point(x_out, y_out);
		}
		/// Спросить размер поля
		static int ask_field_size() {
			string size_in;
			int size_out;
			cout << "What size of field would you prefer?" << endl;
			cin >> size_in;
			if (!string_to_int(size_in, size_out)) {
				cout << "Wrong input. You should print number. Try again." << endl;
				return ask_field_size();
			}
			if (size_out > MAX_RECOMENDED_SIZE_OF_FIELD) {
				cout << "Are you sure? It can be too large." << endl;
				if (!yn_handling())
					return ask_field_size();
			}
			return size_out;
		}
		/// Спросить длину, достаточную для победы
		static int ask_win_combo_size() {
			int size_out;
			string size_in;
			cout << "What size of win-combo would you like?" << endl;
			cin >> size_in;
			if (!(string_to_int(size_in, size_out))) {
				cout << "Wrong input. You should print number. Try again." << endl;
				return ask_win_combo_size();
			}
			return size_out;
		}
		/// Спросить символ для не занятых клеток
		static char ask_empty_cell_symbol(list<Player> players) {
			char out;
			string in;
			cout << "What empty cell symbol would you prefer?" << endl;
			cin >> in;
			if (!(string_to_char(in, out))) {
				cout << "Wrong input. You should print symbol. Try again." << endl;
				return ask_empty_cell_symbol(players);
			}
			if (OperationsWithListOfPlayers::is_symbol_contains(players, out)) {
				cout << "Cheater! This symbol is already selected." << endl;
				return ask_empty_cell_symbol(players);
			}
			return out;
		}
		/// Спросить, хотят ли внести изменения в параметры
		static bool ask_changing_info() {
			cout << "Would you like to change some preferences?" << endl;
			return yn_handling();
		}
		/// Вывести результаты игры
		static void print_final_results(Field &field, string nameWinner, bool draw) {
			Screen::draw(field);
			player_wins(nameWinner, draw);
		}
	};
}
