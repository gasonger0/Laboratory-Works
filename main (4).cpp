#include <iostream>
#include <fstream>
#include <string>

const int FIELD_SIZE{ 8 };															// Размер поля 8 х 8, таковы правила, 
																					// поэтому запишем в константу
const int PLAYER_VALUE{1};															// Фишки игрока, чёрные
const int COMP_VALUE{2};															// Фишки виртуального игрока, белые
const int NULL_CELL{0};																// Пустая клетка

class Game {
private:
	int field[8][8] = {};															// Игровое поле
	List possibleMovesAm;															// Список фишек, которые можно съесть
	List possibleMovesDir;															// Список направлений
public:
	Game() {																		// Конструктор игры, ставит фишки на начальные позиции
		for (int i{}; i < FIELD_SIZE; i++) {		
			for (int j{}; j < FIELD_SIZE; j++) {
				field[i][j] = NULL_CELL;
			}
		}
		field[3][3] = COMP_VALUE;													// Ставим начальные условия
		field[3][4] = PLAYER_VALUE;													// По правилам, в центре доски 4 фишки
		field[4][3] = PLAYER_VALUE;													// 2 - белые, 1 - чёрные
		field[4][4] = COMP_VALUE;
	}

	void load_saves() {																// Функция заргузки сохрнений из файла .txt в
																					// директории игры, позиции хранятся в
																					// виде матрицы значений
		std::ifstream saves;														// Создаём переменную для входного файла	
		saves.open("saves.txt");													// Открываем файл с сохранениями
		if (saves.is_open()) {														// Если файл удалось открыть, действуем дальше
			std::string save_buf;													// Буффер для строк с данными
			int i{}, j{}, k{};														// i строк в файле и поле, j столбцов в файле,
																					// k столбцов в поле
			while(i < FIELD_SIZE){													// Обход строк
				getline(saves, save_buf);											// Пишем в буффер строку из файла
				while(k < FIELD_SIZE){												// Обход столбцов каждой строки
					if ((save_buf[j] == '0') || (save_buf[j] == '1') ||				// Проверка символов на корректность
						(save_buf[j] == '2') || (save_buf[j] == '\n') || 
						(save_buf[j] == ' ')) {

						if ((save_buf[j] == '0') || (save_buf[j] == '1')			// Проверка, является ли символ значащим значением (0, 1 или 2) 
							|| (save_buf[j] == '2')) {					
							field[i][k] = static_cast<int>(save_buf[j]) - 48;		// Пишем проверенный символ из буффера в наше поле
							k++;													// Переход к след. стобцу поля
						}
						j++;														// Переход к следующему символу в строке
					}
					else {							
						std::cout << "Saves are corrupted!!! Exiting the game";
						exit(3);													// Если проверка не пройдена, значит в файле
																					// есть посторонние символы.
					}
				}
				i++;																// Переход к следующей строке поля
				j = 0;																// Обнуляем счётчик символов, чтобы начать
																					// с первого в новой строке
				k = 0;
				std::fill(std::begin(save_buf), std::end(save_buf), '-');
																					// Чистка буфера
			}
			saves.close();															// Закрываем файл сохранения
		}
		else {
			std::cout << "cannot open file.";										// Если файл не открылся, выход
			exit(1);
		}
	}

	void score() {																	// Оценочная функция
		int wh{0}, blk{0};															// Переменные для хранения фишек
		for (int i{}; i < FIELD_SIZE; i++) {										// Обход строк поля
			for (int j{}; j < FIELD_SIZE; j++) {									// Обход столбцов поля
				if (field[i][j] == PLAYER_VALUE) {									// Единица - чёрная фишка
					blk += 1;
				}
				else if (field[i][j] == COMP_VALUE) {								// Двойка - белая фишка
					wh += 1;
				}
			}
		}
		if (wh > blk) {																// Если больше белых
			std::cout << "whites wins with " << wh << " points." << std::endl;
		}
		else if(wh < blk) {															// Если больше чёрных
			std::cout << "blacks wins with " << blk << " points." << std::endl;
		}
		else {																		// Если фишек равное кол-во
			std::cout << "Chanses are equal";
		}
	}

	void getMoves() {
		// Схема работы: в цикле перебираем кажду клетку, и, если она принадлежит COMP'у, перебираем для неё направления хода.
		// После работы каждого направления, записываем его код и кол-во фишек в 2 списка.
		// Таким образом, чтобы узнать, какое направление имеет больший вес, ищем в списке направлений моменты, где координата
		// обнуляется

		/*
		  Коды направлений:
		     0 1 2
		     3 Ф 4
		     5 6 7     , где ф - фишка
		*/
		for (int i{}; i < FIELD_SIZE; i++) {										// Обход столбцов поля
			for (int j{}; j < FIELD_SIZE; j++) {									// Обход рядов поля
				if (field[i][j] == COMP_VALUE) {									// Если в клетке фишка компьютера

					for (int d{1}; ((i-d) >= 0)&&((j+d) < FIELD_SIZE); d++){		// (0) Проход по диагонали
						if(field[i-d][j+d] == PLAYER_VALUE){						// Если в клетке фишка противника,
							continue;												// Продолжаем
						}else if(field[i-d][j+d] == '0'){							// Если клетка пустая
							possibleMovesAm.insert(d);								// Вставляем количество съеденных фишек
							possibleMovesDir.insert(0);								// Вставляем направление хода
							break;
						}else if(field[i-d][j+d] == COMP_VALUE){
							posibleMovesAm.insert(d);
							posibleMovesDir.insert(0);
						}
					}
					for (int y{FIELD_SIZE-1}; y > j; y--) {							// (1) Проход по вертикали сверху вниз
						if(field[i][y] == PLAYER_VALUE){							// Если в клетке фишка противника,
							continue;												// Продолжаем
						}else if(field[i][y] == '0'){								// Если клетка пустая
							possibleMovesAm.insert(d);								// Вставляем количество съеденных фишек
							possibleMovesDir.insert(0);								// Вставляем направление хода
							break;
						}else if(field[i][y] == COMP_VALUE){
							posibleMovesAm.insert(d);
							posibleMovesDir.insert(0);
						}
					}
					for (int d{1};((i+d) < FIELD_SIZE)&&((j+d) < FIELD_SIZE); d++){ // (2) Проход по диагонали
						if(field[i+d][j+d] == PLAYER_VALUE){						// Если в клетке фишка противника,
							continue;												// Продолжаем
						}else if(field[i+d][j+d] == '0'){							// Если клетка пустая
							possibleMovesAm.insert(d);								// Вставляем количество съеденных фишек
							possibleMovesDir.insert(0);								// Вставляем направление хода
							break;
						}else if(field[i+d][j+d] == COMP_VALUE){
							posibleMovesAm.insert(d);
							posibleMovesDir.insert(0);
						}
					}
					for (int x{}; x < i; x++){										// (3) Проход по горизонтали слева направо
						if(field[x][j] == PLAYER_VALUE){							// Если в клетке фишка противника,
							continue;												// Продолжаем
						}else if(field[x][j] == '0'){								// Если клетка пустая
							possibleMovesAm.insert(d);								// Вставляем количество съеденных фишек
							possibleMovesDir.insert(0);								// Вставляем направление хода
							break;
						}else if(field[x][j] == COMP_VALUE){
							posibleMovesAm.insert(d);
							posibleMovesDir.insert(0);
						}
					}
					for (int x{FIELD_SIZE-1}; x > i; x--) {							// (4) Проход по горизонтали справа налево
						if(field[x][j] == PLAYER_VALUE){							// Если в клетке фишка противника,
							continue;												// Продолжаем
						}else if(field[x][j] == '0'){								// Если клетка пустая
							possibleMovesAm.insert(d);								// Вставляем количество съеденных фишек
							possibleMovesDir.insert(0);								// Вставляем направление хода
							break;
						}else if(field[x][j] == COMP_VALUE){
							posibleMovesAm.insert(d);
							posibleMovesDir.insert(0);
						}
					}
					for (int d{1};((i-d) >= 0)&&((j-d) >= 0); d++){					// (5) Проход по диагонали
						if(field[i-d][j-d] == PLAYER_VALUE){						// Если в клетке фишка противника,
							continue;												// Продолжаем
						}else if(field[i-d][j-d] == '0'){							// Если клетка пустая
							possibleMovesAm.insert(d);								// Вставляем количество съеденных фишек
							possibleMovesDir.insert(0);								// Вставляем направление хода
							break;
						}else if(field[i-d][j-d] == COMP_VALUE){
							posibleMovesAm.insert(d);
							posibleMovesDir.insert(0);
						}
					}
					for (int y{}; y < j; y++) {										// (6) Проход по вертикали снизу вверх
						if(field[i][y] == PLAYER_VALUE){							// Если в клетке фишка противника,
							continue;												// Продолжаем
						}else if(field[i][y] == '0'){								// Если клетка пустая
							possibleMovesAm.insert(d);								// Вставляем количество съеденных фишек
							possibleMovesDir.insert(0);								// Вставляем направление хода
							break;
						}else if(field[i][y] == COMP_VALUE){
							posibleMovesAm.insert(d);
							posibleMovesDir.insert(0);
						}
					}
					for (int d{1};((i+d) < FIELD_SIZE)&&((j-d) >= 0); d++){			// (7) Проход по диагонали
						if(field[i+d][j-d] == PLAYER_VALUE){						// Если в клетке фишка противника,
							continue;												// Продолжаем
						}else if(field[i+d][j-d] == '0'){							// Если клетка пустая
							possibleMovesAm.insert(d);								// Вставляем количество съеденных фишек
							possibleMovesDir.insert(0);								// Вставляем направление хода
							break;
						}else if(field[i+d][j-d] == COMP_VALUE){
							posibleMovesAm.insert(d);
							posibleMovesDir.insert(0);
						}
					}
				}
			}
		}
	}
};

int main() {

	char choice;																	// Переменная для хранения выбора о загрузке
																					// сейвов
	std::cout << "This is Reversi game. Would you like to load saves?[y/n] ";		// Спрашиваем о загрузке сохранений
	try {
		std::cin >> choice;															// Записываем ответ
	}
	catch (std::exception e) {
		std::cout << "Enter data in correct format!";								// ОБрабатываем исключения
	}

	Game start;																		// Объект, в котором и будет игра
	if ((choice == 'y')||(choice == 'Y')){											// Если Нужно загрузить сейвы
		start.load_saves();															// Производим загрузку
	}
	else if ((choice == 'n') || (choice == 'N')) {}									// Иначе не загружаем
	else {																			// А если выбор некорректен, выходим из
																					// программы с соответствующим кодом ошибки
		std::cout << "Your choice cannot be correct. Program is exiting, read user's manual please." << std::endl;
		exit(1);
	}

	start.score();																	// Вызов оценочной функции
	return 0;
}
