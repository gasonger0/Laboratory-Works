#include "list.h"										//заголовочный файл со списком
#include <string>
#include <fstream> 

#define NZ 8												//количество неотрицательных элементов

class Matrix {
private:
	List LI = List();												//столбцы
	List LJ = List();												//начало строки
	List A = List();													//значения
public:

	Matrix() {
		std::ifstream in_file;
		in_file.open("in.txt");
		if (in_file.is_open()) {
			std::string buf;
			int x{};
			while (std::getline(in_file, buf)) {
				x = 0;
				for (int a{}; buf[a] != NULL; a++) {
					if ((buf[a] != ' ') && (buf[a] != '\n') && (buf[a] != '0')) {
						try {
							A.insert(static_cast<int>(buf[a] - '0'));
						}
						catch (std::exception e) {
							std::cout << "Input file doesn't has integers\n";
							exit(1);
						}
						LI.insert(x);
					}
					if ((buf[a] != ' ') && (buf[a] != '\n')) {
						x += 1;
					}
				}
			}
			int j{};
			for (int i{ 0 }; A[i] != NULL; i++) {
				if (i == 0) {
					LJ.insert(i);
					j++;
					continue;
				}
				if (LI[i]->value <= LI[i - 1]->value) {
					LJ.insert(i);
					j++;
				}
				if ((LJ[j] != NULL) && (A[i] != NULL) &&(LJ[j]->value != A[i]->value) && (A[i + 1] == NULL)) {
					LJ.insert(i + 1);
				}
			}
		}
		else {
			std::cout << "Failed to open file.\n Check file name or path.";
			exit(1);
		}
	}

	Matrix(int* x, int* y, int* a) {
		for (int i{}; i < NZ; i++) {
			LI.insert(y[i]);
		}
		for (int i{}; i < NZ; i++) {
			A.insert(a[i]);
		}
		int j{};
		for (int i{ 0 }; i < NZ; i++) {
			if (i == 0) {
				LJ.insert(i);
				j++;
				continue;
			}
			if (x[i] > x[i - 1]) {
				LJ.insert(i);
				j++;
			}
		}

		if (!(LJ[j - 1]->value == NZ)) {
			LJ.insert(NZ);
		}
		delete[] x;
		delete[] y;
		delete[] a;
	}


	void print_ch() {
		A.print();
		LI.print();
		LJ.print();
	}

	void move() {
		List new_A;
		int k{};
		while (A[k] != NULL) {
			k++;
		}
		new_A.insert(A[k - 1]->value);

		for (int i{}; A[i + 1] != NULL; i++) {
			new_A.insert(A[i]->value);
		}
		A = NULL;
		A = new_A;

		List new_LI;

		if (LI[k - 1]->value != 3) {
			new_LI.insert((LI[k]->value) + 1);
		}
		else {
			new_LI.insert(0);
		}
		for (int i{}; LI[i + 1] != NULL; i++) {
			if (LI[i]->value != 3) {
				new_LI.insert((LI[i]->value) + 1);
			}
			else {
				new_LI.insert(0);
			}
		}
		LI = NULL;
		LI = new_LI;

		List new_LJ;
		int j{};
		for (int i{ 0 }; i < NZ; i++) {
			if (i == 0) {
				new_LJ.insert(i);
				j++;
				continue;
			}
			if (LI[i]->value <= LI[i - 1]->value) {
				new_LJ.insert(i);
				j++;
			}
		}

		if (!(LJ[j - 1]->value == NZ)) {
			new_LJ.insert(NZ);
		}
		LJ = NULL;
		LJ = new_LJ;
	}
};

int main() {
	Matrix Mtrx;
	Mtrx.print_ch();
	Mtrx.move();
	std::cout << std::endl << "Move done." << std::endl << std::endl;
	Mtrx.print_ch();
	return 0;
}
