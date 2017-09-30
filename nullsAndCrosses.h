/// Более рациональный отлов исключений и изменения архитектуры в пользу более абстрактной
#include <cstdlib>
#include <string>
#include <iostream>
#include <list>
#define MAX_RECOMMENDED_SIZE_OF_FIELD 35 // TODO: Убрать глобальную нетипизированную константу в класс

using namespace std;

namespace nullsAndCrosses {
    /// Класс для хранения точки
    class Point{
        int x, y;
    public:
        Point () {
            x = y = 0;
        }
        Point (const int x1, const int y1) {
            x = x1;
            y = y1;
        }
        void setX (const int x1) {
            x = x1;
        }
        void setY (const int y1) {
            y = y1;
        }
        int getX() const {
            return x;
        }
        int getY() const {
            return y;
        }
    };

    /// Класс для работы с полем
    class Field{
        char ** field, emptyCell;
        int size;
        char getCell (const int x, const int y) const{
            return field [size-y-1][size-x-1]; // TODO: exceptions handling
        }
        void setCell (const int x, const int y, const char newSymbol){
            field [size-y-1] [size-x-1] = newSymbol; // TODO: exceptions handling
        }
    public :
        Field() {
            field = NULL;
            emptyCell = 0;
            size = 0;
        }
        Field(const char symbol, const int s){
            size = s;
            emptyCell = symbol;
            field = new char * [size];
            for (int i = 0; i < size; i ++) {
                field [i] = new char [size];
                for (int j = 0; j < size; j ++)
                    field [i][j] = emptyCell;
            }
        }
        ~Field () {
        for(int i=0; i<size; i++)
            delete field[i];
        delete field;
        }
        void clear(){
            for(int i = 0; i < size; i++)
                for(int j = 0; j < size; j++)
                    field [i][j] = emptyCell;
        }
        char getCell (const Point point) const{
            return getCell (point.getX(), point.getY());
        }
        void setCell (const Point point, const char newSymbol){
            setCell (point.getX(), point.getY(), newSymbol);
        }
        void initialize (const char symbol, const int s) {
            //if(Field!=nullptr) TODO: test it
            //    throw string("Field::initialize. Error. It has been initialized.");
            size = s;
            emptyCell = symbol;
            field = new char * [size];
            for (int i = 0; i < size; i ++) {
                field [i] = new char [size];
                for (int j = 0; j < size; j ++)
                    field [i][j] = emptyCell;
            }
        }
        int getSize() const{
            return size;
        }
        bool isCoordCorrect(const Point point) const{
            if (point.getX()>=0 && point.getX()<size && point.getY()>=0 && point.getY()<size)
                return true;
            return false;
        }
        char getEmptySymbol() const{
            return emptyCell;
        }
    };

    /// Класс для работы с выводом
    class Screen {
        static string getField(Field &field){
            string str;
            for(int i = 0; i < field.getSize(); i++){
                for(int j = 0; j < field.getSize(); j++){
                    str += field.getCell(Point(i, j));
                    if(j < field.getSize() - 1)
                        str += " ";
                    else
                        str += '\n';
                }
            }
            return str;
        }
    public:
        static void clear(){
            system("clear");
        }
        static void draw(Field &field){
            clear();
            cout << getField(field);
        }

    };

    /// Класс для хранения информации об игроке
    class Player {
        string name;
        char symbol;
    public:
        Player(){
            name = "Jonn Doe";
            symbol = 'x';
        }
        Player(string n, char sym){
            name = n;
            symbol = sym;
        }
        string getName() {return name;}
        char getSymbol() {return symbol;}
    };

    /// Класс операций со списком игроков
    class OperationsWithListOfPlayers{
    public :
        static bool isNameContain (list<Player> players, string newName) {
            if(players.empty())
                return false;
            if(players.front().getName()==newName)
                return true;
            players.pop_front();
            return isNameContain (players, newName);
        }
        static bool isSymbolContain (list<Player> players, char newSymbol) {
            if(players.empty())
                return false;
            if(players.front().getSymbol()==newSymbol)
                return true;
            players.pop_front();
            return isSymbolContain (players, newSymbol);
        }
    };

    /// Класс взаимодействия с пользователем
    class Dialog {
        static bool yn_handling(){
            string yn_in;
            bool yn_out;
            cin >> yn_in;
            if (!stringToBool(yn_in, yn_out)){
                cout << "Wrong input. You should print y or n. Try again." << endl;
                return yn_handling();
            }
            return yn_out;
        }
        /// Возвращает статус операции
        static bool stringToChar(const string in, char &out){
            if(in.length()>1)
                return false;
            out = in.at(0);
            return true;
        }
        /// Возвращает статус операции
        static bool stringToInt(string in, int &out){
            out = 0;
            for(int i=0; i<in.length(); i++){
                if(in.at(i)>'9' || in.at(i)<'0')
                    return false;
                out *= 10;
                out += in.at(i) - '0';
            }
            return true;
        }
        /// Возвращает статус операции
        static bool stringToBool(string in, bool &out){
            if(in.length()>1)
                return false;
            if(in.at(0) == 'y'){
                out = true;
                return true;
            }
            if(in.at(0)=='n'){
                out = false;
                return true;
            }
            return false;
        }
        static string askPlayers_name() {
            string name;
            cout << "Print your name." << endl;
            cin >> name;
            return name;
        }
        static char askPlayers_symbol(){
            string symbol;
            char symbolC;
            cout << "Print your symbol." << endl;
            cin >> symbol;
            if(!(stringToChar(symbol, symbolC))){
                cout << "Wrong input. You should print symbol." << endl;
                return askPlayers_symbol();
            }
            return symbolC;
        }
        static bool askPlayers_ifWantAddNew () {
            string in;
            bool out;
            cout << "Would you like to add more players?" << endl;
            return yn_handling();
        }
        static void playerWins(string name, bool noOne){
            if(noOne){
                cout << "Draw!" <<endl;
                return;
            }
            cout << name << " wins!"<< endl;
        }
    public:
        /// Запрос информации об игроках
        static list <Player> askPlayersInfo(){
            Screen::clear();
            list <Player> (players);
            string name;
            char symbol;
            do{
                do{
                    name = askPlayers_name();
                }while (OperationsWithListOfPlayers::isNameContain(players, name));
                do{
                    symbol = askPlayers_symbol();
                }while (OperationsWithListOfPlayers::isSymbolContain(players, symbol));
                players.push_back(Player(name, symbol));
            }while(askPlayers_ifWantAddNew());
            return players;
        }
        /// Спросить хотят ли начать новую игру
        static bool askStartNewOrNo(){
            cout << "Would you like to start new game? (y/n)" << endl;
            return yn_handling();
        }
        /// Отрисовать поле и запросить координаты нового символа
        static Point askNewSymbolCoord(string name){
            // Не очищаем экран, чтобы не стереть отображение поля
            string x_in, y_in;
            int x_out, y_out;
            cout << name << ", where do you prefer to put symbol? (x, y)" << endl;
            cin >> x_in >> y_in;
            if (!stringToInt(x_in, x_out) || !stringToInt(y_in, y_out)){
                cout << "Wrong input. You should print coords of new point. Try again" << endl;
                return askNewSymbolCoord(name);
            }
            x_out --; // Пользователь нумерует с единицы, а мы с нуля
            y_out --;
            return Point(x_out, y_out);
        }
        /// Спросить размер поля
        static int askFieldSize(){
            string size_in;
            int size_out;
            cout << "What size of field would you prefer?" << endl;
            cin >> size_in;
            if (!stringToInt(size_in, size_out)){
                cout << "Wrong input. You should print number. Try again." << endl;
                return askFieldSize();
            }
            if (size_out>MAX_RECOMMENDED_SIZE_OF_FIELD){
                cout << "Are you sure? It can be too large. (y/n)" << endl;
                if (!yn_handling())
                    return askFieldSize();
            }
            return size_out;
        }
        /// Спросить длину, достаточную для победы
        static int askWinComboSize(){
            int size_out;
            string size_in;
            cout << "What size of win-combo would you like?" << endl;
            cin >> size_in;
            if(!(stringToInt(size_in, size_out))){
                cout << "Wrong input. You should print number. Try again." << endl;
                return askWinComboSize();
            }
            return size_out;
        }
        /// Спросить символ для не занятых клеток
        static char askEmptyCellSymbol(){
            char out;
            string in;
            cout << "What empty cell symbol would you prefer?" << endl;
            cin >> in;
            if(!(stringToChar(in, out))){
                cout << "Wrong input. You should print symbol. Try again." << endl;
                return askEmptyCellSymbol();
            }
            return out;
        }
        /// Спросить, хотят ли внести изменения в параметры
        static bool askChangingInfo(){
            cout << "Would you like to change some preferences? (y/n)" << endl;
            return yn_handling();
        }
        /// Вывести результаты игры
        static void printFinalResults(Field &field, string nameWinner, bool draw){
            Screen::draw(field);
            playerWins(nameWinner, draw);
        }
    };

    /// Класс обработки игры
    class Game {
        list<Player> (players);
        Field field;
        int sizeWinCombo, numPlayers;
        /// Инициализация информации об игре
        void initializeInfo(){
            players = Dialog::askPlayersInfo();
            sizeWinCombo = Dialog::askWinComboSize();
        }
        /// Перезапуск с очисткой поля и возможностью поменять информацию
        void restartGame(){
            field.clear();
            if(Dialog::askChangingInfo())
                initializeInfo();
            continueGame();
        }
        /// Проверка, победит ли игрок после постановки новой точки
        bool isWinOrNo(const Point newPoint, const char playerSymbol) const {
            int counterVert = 0, counterGor = 0, counterDi1 = 0, counterDi2 = 0, size = field.getSize();
            for(int i=0; i<size; i++){
                if(field.getCell(Point(newPoint.getY(), i))==playerSymbol) {
                   counterVert++;
                   if(counterVert>=sizeWinCombo)
                       return true;
                }
               else counterVert = 0;
               if(field.getCell(Point(i, newPoint.getX()))==playerSymbol) {
                   counterGor++;
                   if(counterGor>=sizeWinCombo)
                       return true;
                }
               else counterGor = 0;
               if(field.getCell(Point(i, i))==playerSymbol) {
                   counterDi1++;
                   if(counterDi1>=sizeWinCombo)
                       return true;
                }
               else counterDi1 = 0;
               if(field.getCell(Point(size-i-1, i))==playerSymbol) {
                   counterDi2++;
                   if(counterDi2>=sizeWinCombo)
                       return true;
                }
               else counterDi2 = 0;
            }
            return false;
        }
        bool isDrawOrNo (const int num_steps, const int size) const {
            return num_steps<size*size;
        }
        void stepOfGame(Player playerNow){
            Point newPoint;
            newPoint = Dialog::askNewSymbolCoord(playerNow.getName());
            if (!field.isCoordCorrect(newPoint)){
                cout << "Wrong input. There are no cell with this coords." << endl;
                stepOfGame(playerNow);
            }
            if (field.getCell(newPoint)!=field.getEmptySymbol()){
                cout << "Wrong input. This cell is already used." << endl;
                stepOfGame(playerNow);
            }
            field.setCell(newPoint, playerNow.getSymbol());
        }
        /// Продолжить игру (без инициализации)
        void continueGame(){
            Point newPoint;
            Player playerNow;
            int stepCounter = 0; // Для опеределения ничьей
            do{
                Screen::draw (field);
                playerNow = players.front();
                stepOfGame(playerNow);
                stepCounter++;
                players.pop_front();
                players.push_back(playerNow);
            } while (!isWinOrNo(newPoint, playerNow.getSymbol()) || !isDrawOrNo(stepCounter, field.getSize()));
            Dialog::printFinalResults(field  ,playerNow.getName(), !isWinOrNo(newPoint, playerNow.getSymbol()));
            if(Dialog::askStartNewOrNo())
                restartGame();
        }
    public:
        /// Начать игру (с инициализацией)
        void newGame(){
            initializeInfo();
            field.initialize(Dialog::askEmptyCellSymbol(), Dialog::askFieldSize());
            continueGame();
        }
    };
}