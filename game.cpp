#include "game.h"

namespace nullsAndCrosses {
	/// ������������� ���������� �� ����
	void Game::initializeInfo() {
		players = Dialog::askPlayersInfo();
		sizeWinCombo = Dialog::askWinComboSize();
	}
	/// ���������� � �������� ���� � ������������ �������� ����������
	void Game::restartGame() {
		field.clear();
		if (Dialog::askChangingInfo())
			initializeInfo();
		continueGame();
	}
	/// ��������, ������� �� ����� ����� ���������� ����� �����
	bool Game::isWinOrNo(const Point newPoint, const char playerSymbol) const {
		int counterVert = 0, counterGor = 0, counterDi1 = 0, counterDi2 = 0, size = field.getSize();
		for (int i = 0; i < size; i++) {
			if (field.getCell(Point(newPoint.getY(), i)) == playerSymbol) {
				counterVert++;
				if (counterVert >= sizeWinCombo)
					return true;
			}
			else counterVert = 0;
			if (field.getCell(Point(i, newPoint.getX())) == playerSymbol) {
				counterGor++;
				if (counterGor >= sizeWinCombo)
					return true;
			}
			else counterGor = 0;
			if (field.getCell(Point(i, i)) == playerSymbol) {
				counterDi1++;
				if (counterDi1 >= sizeWinCombo)
					return true;
			}
			else counterDi1 = 0;
			if (field.getCell(Point(size - i - 1, i)) == playerSymbol) {
				counterDi2++;
				if (counterDi2 >= sizeWinCombo)
					return true;
			}
			else counterDi2 = 0;
		}
		return false;
	}
	/// �������� �� �����
	bool Game::isDrawOrNo(const int num_steps, const int size) const {
		return num_steps < size*size;
	}
	/// ��������� 1 ���� ���� (�� 1 �����)
	void Game::stepOfGame(Player playerNow) {
		Point newPoint;
		newPoint = Dialog::askNewSymbolCoord(playerNow.getName());
		if (!field.isCoordCorrect(newPoint)) {
			cout << "Wrong input. There are no cell with this coords." << endl;
			stepOfGame(playerNow);
		}
		if (field.getCell(newPoint) != field.getEmptySymbol()) {
			cout << "Wrong input. This cell is already used." << endl;
			stepOfGame(playerNow);
		}
		field.setCell(newPoint, playerNow.getSymbol());
	}
	/// ���������� ���� (��� �������������)
	void Game::continueGame() {
		Point newPoint;
		Player playerNow;
		int stepCounter = 0; // ��� ������������ ������
		do {
			Screen::draw(field);
			playerNow = players.front();
			stepOfGame(playerNow);
			stepCounter++;
			players.pop_front();
			players.push_back(playerNow);
		} while (!isWinOrNo(newPoint, playerNow.getSymbol()) || !isDrawOrNo(stepCounter, field.getSize()));
		Dialog::printFinalResults(field, playerNow.getName(), !isWinOrNo(newPoint, playerNow.getSymbol()));
		if (Dialog::askStartNewOrNo())
			restartGame();
	}
	/// ������ ���� (� ��������������)
	void Game::newGame() {
		initializeInfo();
		field.initialize(Dialog::askEmptyCellSymbol(), Dialog::askFieldSize());
		continueGame();
	}
}