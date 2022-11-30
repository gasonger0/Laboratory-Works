#include <iostream>
#include <fstream>
#include <string>

const int FIELD_SIZE{ 8 };															// ������ ���� 8 � 8, ������ �������, 
																					// ������� ������� � ���������
const int PLAYER_VALUE{1};															// ����� ������, ������
const int COMP_VALUE{2};															// ����� ������������ ������, �����
const int NULL_CELL{0};																// ������ ������

class Game {
private:
	int field[8][8] = {};															// ������� ����
	List possibleMovesAm;															// ������ �����, ������� ����� ������
	List possibleMovesDir;															// ������ �����������
public:
	Game() {																		// ����������� ����, ������ ����� �� ��������� �������
		for (int i{}; i < FIELD_SIZE; i++) {		
			for (int j{}; j < FIELD_SIZE; j++) {
				field[i][j] = NULL_CELL;
			}
		}
		field[3][3] = COMP_VALUE;													// ������ ��������� �������
		field[3][4] = PLAYER_VALUE;													// �� ��������, � ������ ����� 4 �����
		field[4][3] = PLAYER_VALUE;													// 2 - �����, 1 - ������
		field[4][4] = COMP_VALUE;
	}

	void load_saves() {																// ������� �������� ��������� �� ����� .txt �
																					// ���������� ����, ������� �������� �
																					// ���� ������� ��������
		std::ifstream saves;														// ������ ���������� ��� �������� �����	
		saves.open("saves.txt");													// ��������� ���� � ������������
		if (saves.is_open()) {														// ���� ���� ������� �������, ��������� ������
			std::string save_buf;													// ������ ��� ����� � �������
			int i{}, j{}, k{};														// i ����� � ����� � ����, j �������� � �����,
																					// k �������� � ����
			while(i < FIELD_SIZE){													// ����� �����
				getline(saves, save_buf);											// ����� � ������ ������ �� �����
				while(k < FIELD_SIZE){												// ����� �������� ������ ������
					if ((save_buf[j] == '0') || (save_buf[j] == '1') ||				// �������� �������� �� ������������
						(save_buf[j] == '2') || (save_buf[j] == '\n') || 
						(save_buf[j] == ' ')) {

						if ((save_buf[j] == '0') || (save_buf[j] == '1')			// ��������, �������� �� ������ �������� ��������� (0, 1 ��� 2) 
							|| (save_buf[j] == '2')) {					
							field[i][k] = static_cast<int>(save_buf[j]) - 48;		// ����� ����������� ������ �� ������� � ���� ����
							k++;													// ������� � ����. ������ ����
						}
						j++;														// ������� � ���������� ������� � ������
					}
					else {							
						std::cout << "Saves are corrupted!!! Exiting the game";
						exit(3);													// ���� �������� �� ��������, ������ � �����
																					// ���� ����������� �������.
					}
				}
				i++;																// ������� � ��������� ������ ����
				j = 0;																// �������� ������� ��������, ����� ������
																					// � ������� � ����� ������
				k = 0;
				std::fill(std::begin(save_buf), std::end(save_buf), '-');
																					// ������ ������
			}
			saves.close();															// ��������� ���� ����������
		}
		else {
			std::cout << "cannot open file.";										// ���� ���� �� ��������, �����
			exit(1);
		}
	}

	void score() {																	// ��������� �������
		int wh{0}, blk{0};															// ���������� ��� �������� �����
		for (int i{}; i < FIELD_SIZE; i++) {										// ����� ����� ����
			for (int j{}; j < FIELD_SIZE; j++) {									// ����� �������� ����
				if (field[i][j] == PLAYER_VALUE) {									// ������� - ������ �����
					blk += 1;
				}
				else if (field[i][j] == COMP_VALUE) {								// ������ - ����� �����
					wh += 1;
				}
			}
		}
		if (wh > blk) {																// ���� ������ �����
			std::cout << "whites wins with " << wh << " points." << std::endl;
		}
		else if(wh < blk) {															// ���� ������ ������
			std::cout << "blacks wins with " << blk << " points." << std::endl;
		}
		else {																		// ���� ����� ������ ���-��
			std::cout << "Chanses are equal";
		}
	}

	void getMoves() {
		// ����� ������: � ����� ���������� ����� ������, �, ���� ��� ����������� COMP'�, ���������� ��� �� ����������� ����.
		// ����� ������ ������� �����������, ���������� ��� ��� � ���-�� ����� � 2 ������.
		// ����� �������, ����� ������, ����� ����������� ����� ������� ���, ���� � ������ ����������� �������, ��� ����������
		// ����������

		/*
		  ���� �����������:
		     0 1 2
		     3 � 4
		     5 6 7     , ��� � - �����
		*/
		for (int i{}; i < FIELD_SIZE; i++) {										// ����� �������� ����
			for (int j{}; j < FIELD_SIZE; j++) {									// ����� ����� ����
				if (field[i][j] == COMP_VALUE) {									// ���� � ������ ����� ����������

					for (int d{1}; ((i-d) >= 0)&&((j+d) < FIELD_SIZE); d++){		// (0) ������ �� ���������
						if(field[i-d][j+d] == PLAYER_VALUE){						// ���� � ������ ����� ����������,
							continue;												// ����������
						}else if(field[i-d][j+d] == '0'){							// ���� ������ ������
							possibleMovesAm.insert(d);								// ��������� ���������� ��������� �����
							possibleMovesDir.insert(0);								// ��������� ����������� ����
							break;
						}else if(field[i-d][j+d] == COMP_VALUE){
							posibleMovesAm.insert(d);
							posibleMovesDir.insert(0);
						}
					}
					for (int y{FIELD_SIZE-1}; y > j; y--) {							// (1) ������ �� ��������� ������ ����
						if(field[i][y] == PLAYER_VALUE){							// ���� � ������ ����� ����������,
							continue;												// ����������
						}else if(field[i][y] == '0'){								// ���� ������ ������
							possibleMovesAm.insert(d);								// ��������� ���������� ��������� �����
							possibleMovesDir.insert(0);								// ��������� ����������� ����
							break;
						}else if(field[i][y] == COMP_VALUE){
							posibleMovesAm.insert(d);
							posibleMovesDir.insert(0);
						}
					}
					for (int d{1};((i+d) < FIELD_SIZE)&&((j+d) < FIELD_SIZE); d++){ // (2) ������ �� ���������
						if(field[i+d][j+d] == PLAYER_VALUE){						// ���� � ������ ����� ����������,
							continue;												// ����������
						}else if(field[i+d][j+d] == '0'){							// ���� ������ ������
							possibleMovesAm.insert(d);								// ��������� ���������� ��������� �����
							possibleMovesDir.insert(0);								// ��������� ����������� ����
							break;
						}else if(field[i+d][j+d] == COMP_VALUE){
							posibleMovesAm.insert(d);
							posibleMovesDir.insert(0);
						}
					}
					for (int x{}; x < i; x++){										// (3) ������ �� ����������� ����� �������
						if(field[x][j] == PLAYER_VALUE){							// ���� � ������ ����� ����������,
							continue;												// ����������
						}else if(field[x][j] == '0'){								// ���� ������ ������
							possibleMovesAm.insert(d);								// ��������� ���������� ��������� �����
							possibleMovesDir.insert(0);								// ��������� ����������� ����
							break;
						}else if(field[x][j] == COMP_VALUE){
							posibleMovesAm.insert(d);
							posibleMovesDir.insert(0);
						}
					}
					for (int x{FIELD_SIZE-1}; x > i; x--) {							// (4) ������ �� ����������� ������ ������
						if(field[x][j] == PLAYER_VALUE){							// ���� � ������ ����� ����������,
							continue;												// ����������
						}else if(field[x][j] == '0'){								// ���� ������ ������
							possibleMovesAm.insert(d);								// ��������� ���������� ��������� �����
							possibleMovesDir.insert(0);								// ��������� ����������� ����
							break;
						}else if(field[x][j] == COMP_VALUE){
							posibleMovesAm.insert(d);
							posibleMovesDir.insert(0);
						}
					}
					for (int d{1};((i-d) >= 0)&&((j-d) >= 0); d++){					// (5) ������ �� ���������
						if(field[i-d][j-d] == PLAYER_VALUE){						// ���� � ������ ����� ����������,
							continue;												// ����������
						}else if(field[i-d][j-d] == '0'){							// ���� ������ ������
							possibleMovesAm.insert(d);								// ��������� ���������� ��������� �����
							possibleMovesDir.insert(0);								// ��������� ����������� ����
							break;
						}else if(field[i-d][j-d] == COMP_VALUE){
							posibleMovesAm.insert(d);
							posibleMovesDir.insert(0);
						}
					}
					for (int y{}; y < j; y++) {										// (6) ������ �� ��������� ����� �����
						if(field[i][y] == PLAYER_VALUE){							// ���� � ������ ����� ����������,
							continue;												// ����������
						}else if(field[i][y] == '0'){								// ���� ������ ������
							possibleMovesAm.insert(d);								// ��������� ���������� ��������� �����
							possibleMovesDir.insert(0);								// ��������� ����������� ����
							break;
						}else if(field[i][y] == COMP_VALUE){
							posibleMovesAm.insert(d);
							posibleMovesDir.insert(0);
						}
					}
					for (int d{1};((i+d) < FIELD_SIZE)&&((j-d) >= 0); d++){			// (7) ������ �� ���������
						if(field[i+d][j-d] == PLAYER_VALUE){						// ���� � ������ ����� ����������,
							continue;												// ����������
						}else if(field[i+d][j-d] == '0'){							// ���� ������ ������
							possibleMovesAm.insert(d);								// ��������� ���������� ��������� �����
							possibleMovesDir.insert(0);								// ��������� ����������� ����
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

	char choice;																	// ���������� ��� �������� ������ � ��������
																					// ������
	std::cout << "This is Reversi game. Would you like to load saves?[y/n] ";		// ���������� � �������� ����������
	try {
		std::cin >> choice;															// ���������� �����
	}
	catch (std::exception e) {
		std::cout << "Enter data in correct format!";								// ������������ ����������
	}

	Game start;																		// ������, � ������� � ����� ����
	if ((choice == 'y')||(choice == 'Y')){											// ���� ����� ��������� �����
		start.load_saves();															// ���������� ��������
	}
	else if ((choice == 'n') || (choice == 'N')) {}									// ����� �� ���������
	else {																			// � ���� ����� �����������, ������� ��
																					// ��������� � ��������������� ����� ������
		std::cout << "Your choice cannot be correct. Program is exiting, read user's manual please." << std::endl;
		exit(1);
	}

	start.score();																	// ����� ��������� �������
	return 0;
}
