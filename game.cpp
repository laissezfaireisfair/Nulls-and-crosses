#include "game.h"

namespace nullsAndCrosses {
	/// Инициализация информации об игре
	void Game::initializeInfo() {
		players = Dialog::askPlayersInfo();
		sizeWinCombo = Dialog::askWinComboSize();
	}
	/// Перезапуск с очисткой поля и возможностью поменять информацию
	void Game::restartGame() {
		field.clear();
		if (Dialog::askChangingInfo()) {
			initializeInfo();
			field.clear();
			field.initialize(Dialog::askEmptyCellSymbol(players), Dialog::askFieldSize());
		}
		continueGame();
	}
	/// Функция для подсчёта пользовательских точек на одной диагонали
	int  Game::countDio1WithPoint(const char player, const Point newPoint) const {
		int maxCombo = 0, beginCoordX, beginCoordY, dioLen, size = field.getSize();
		int nowCombo = 0;
		if (newPoint.getX() > newPoint.getY()) {
			beginCoordX = newPoint.getX() - newPoint.getY();
			beginCoordY = 0;
			dioLen = size - beginCoordX;
		}
		else {
			beginCoordX = 0;
			beginCoordY = newPoint.getY() - newPoint.getX();
			dioLen = size - beginCoordY;
		}
		for (int i = 0; i < dioLen; i++) {
			if (field.getCell(Point(beginCoordX + i, beginCoordY + i)) == player)
				nowCombo++;
			else {
				maxCombo = (nowCombo > maxCombo) ? nowCombo : maxCombo;
				nowCombo = 0;
			}
		}
		return (nowCombo > maxCombo) ? nowCombo : maxCombo;
	}
	/// И на другой
	int  Game::countDio2WithPoint(const char player, const Point newPoint) const {
		int maxCombo = 0, nowCombo = 0, xBegin, yBegin, len, size = field.getSize();
		if (newPoint.getX() + newPoint.getY() <= size - 1) {
			xBegin = 0;
			yBegin = newPoint.getX() + newPoint.getY();
			len = yBegin + 1;
		}
		else {
			xBegin = newPoint.getX() + newPoint.getY() - size + 1;
			yBegin = size - 1;
			len = size - xBegin;
		}
		for (int i = 0; i < len; i++) {
			if (field.getCell(Point(xBegin + i, yBegin - i)) == player)
				nowCombo++;
			else {
				maxCombo = (nowCombo > maxCombo) ? nowCombo : maxCombo;
				nowCombo = 0;
			}
		}
		return (nowCombo > maxCombo) ? nowCombo : maxCombo;
	}
	/// Проверка, победит ли игрок после постановки новой точки 
	bool Game::isWinOrNo(const Point newPoint, const char playerSymbol) const {
		int size = field.getSize(), counter1 = 0, counter2 = 0;
		for (int i = 0; i < size; i++) { // Перебор строки и столбца с новой точкой
			if (field.getCell(Point(newPoint.getX(), i)) == playerSymbol) {
				counter1++;
				if (counter1 >= sizeWinCombo)
					return true;
			}
			else
				counter1 = 0;
			if (field.getCell(Point(i, newPoint.getY())) == playerSymbol) {
				counter2++;
				if (counter2 >= sizeWinCombo)
					return true;
			}
			else
				counter2 = 0;
		}
		counter1 = counter2 = 0;
		if (countDio1WithPoint(playerSymbol, newPoint) >= sizeWinCombo)
			return true;
		if (countDio2WithPoint(playerSymbol, newPoint) >= sizeWinCombo)
			return true;
		return false;
	}
	/// Проверка на ничью
	bool Game::isDrawOrNo(const int num_steps, const int size) const {
		return num_steps < size*size;
	}
	/// Обработка 1 хода игры (от 1 юзера)
	Point Game::stepOfGame(Player playerNow) {
		Point newPoint;
		newPoint = Dialog::askNewSymbolCoord(playerNow.getName());
		if (!field.isCoordCorrect(newPoint)) {
			cout << "Wrong input. There are no cell with this coords." << endl;
			return stepOfGame(playerNow);
		}
		if (field.getCell(newPoint) != field.getEmptySymbol()) {
			cout << "Wrong input. This cell is already used." << endl;
			return stepOfGame(playerNow);
			
		}
		field.setCell(newPoint, playerNow.getSymbol());
		return newPoint;
	}
	/// Продолжить игру (без инициализации)
	void Game::continueGame() {
		Point newPoint;
		Player playerNow;
		int stepCounter = 0; // Для опеределения ничьей
		do {
			Screen::draw(field);
			playerNow = players.front();
			newPoint = stepOfGame(playerNow);
			stepCounter++;
			players.pop_front();
			players.push_back(playerNow);
		} while (!isWinOrNo(newPoint, playerNow.getSymbol()) || !isDrawOrNo(stepCounter, field.getSize()));
		Dialog::printFinalResults(field, playerNow.getName(), !isWinOrNo(newPoint, playerNow.getSymbol()));
		if (Dialog::askStartNewOrNo())
			restartGame();
	}
	/// Начать игру (с инициализацией)
	void Game::newGame() {
		initializeInfo();
		field.initialize(Dialog::askEmptyCellSymbol(players), Dialog::askFieldSize());
		continueGame();
	}
}
