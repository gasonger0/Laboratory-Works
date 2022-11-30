#include <iostream>
#include "list.h"
#include <fstream>
#include <string>

struct Tree {

};

class Tree{
	friend int compare(Tree a, Tree b, int i, int j);
	friend int procedure(Tree a, Tree b);
private:
	Tree* bin;																// Список, хранящий в себе структуру дерева
	int rank{};																// Ранг дерева
public:

	Tree(const char * path) {												// Конструктор, составляет дерево и заполняет tree
		std::ifstream in_file;												// Поток на ввод файла
		in_file.open(path);													// Открываем файл
		if (in_file.is_open()) {											// Если удачно, идём дальше
			std::string buffer;												// Буффер для записи в него символов файла
			int i{};														// Счётчик символов в файле
			try {
				std::getline(in_file, buffer);								// Считываем строку файла
			}catch(std::exception e) {
				std::cout << "Cannot read file.\n";
			}
			while (buffer[i] != NULL) {										// Пока в буфере есть символы
				if ((buffer[i] != ' ') && (buffer[i] != '\n')) {			// Если символ - число
					bin.insert(buffer[i], bin);								// Конвертация в числа
				}
				i++;														// Переход к следующему символу
			}
		}
		else {
			std::cout << "Cannot open file.\n";								// Сообщение ошибки, если файл не открылся
		}
	}

	void insert(char _, Tree* cur) {
		if (_ < cur->value){
			if (node->Left == nullptr) {
				node->Left = new Tree(nullptr, nullptr, _x);
			}
			else{
			    AddItem(node->Left, _x);
			    }
			if (_x > node->value)
			    {
			        if (node->Right == nullptr)
			            node->Right = new Tree(nullptr, nullptr, _x);
			        else
			            AddItem(node->Right, _x);
			    }
	}

	
};

/*List compare(Tree first, Tree second, int i, int j) {						// Сравнение деревьев
	if ((first.tree[i] != 0) && (second.tree[j] != 0)) {
		List out_1, out_2;
		if ((i == 0) && (j == 0)) {
			i = 2;
			j = 2;
		}
		else {
			i *= 2;
			j *= 2;
		}
		out_1 = compare(first, second, i, j);
		i++;
		j++;
		out_2 = compare(first, second, i, j);
		int i{};
		List out;
		while (out_1[i] != NULL) {
			out.insert(out_1[i]->value);
			i++;
		}
		i = 0;
		while (out_2[i] != NULL) {
			out.insert(out_2[i]->value);
			i++;
		}
		return first.tree;
	}
}*/

int compare(Tree first, Tree second, int i, int j) {						// Сравнение деревьев
	if ((first.tree[i] != 0) && (second.tree[j] != 0)) {
		int out_1, out_2;
		if ((i == 0) && (j == 0)) {
			i = 2;
			j = 2;
		}
		else {
			i *= 2;
			j *= 2;
		}
		out_1 = compare(first, second, i, j);
		i++;
		j++;
		out_2 = compare(first, second, i, j);
		int out{};
		out += out_1;
		out += out_2;
		return out;
	}
}

int procedure(Tree first, Tree second) {
	int i{}, j{}, k{};
	int out_1, out_2;
	out_1 = compare(first, second, i, j);
	while (first.tree[i] != nullptr) {
		while (second.tree[j] != nullptr) {
			out_2 = compare(first, second, i, j);
			out_1 += out_2;
			j++;
			k = 0;
		}
		i++;
		j = 0;

	}
	return out_1;
}

int main() {
	Tree start("in.txt");
	Tree diff("diff.txt");
	std::cout << start.print() << std::endl << std::endl << diff.print();
	int end = procedure(start, diff);
	std::cout << end;
	return 0;
}


// Задание:
// Дано бинарное дерево. Найти все поддеревья, структура которых совпадает с заданной.

//#include <iostream>
//
//int tabs = 0;
////Структура бинарного дерева 
//struct Tree{
//    int value;
//    Tree *Right, *Left;
//};
//
//class Mytree {
//
//public:
//    Tree* Root;
//    int account = 1;
//
//    Mytree()
//    {
//        int num{ 0 }, value{ 0 };
//        std::cout << "Enter num of values\n";
//        std::cin >> num;
//        std::cout << "Randomly fill in the structure\n\n";
//        for (int i = 0; i < num; i++)
//        {
//            std::cin >> value;
//            if (i == 0)
//            {
//                Root = new Tree(nullptr, nullptr, value);
//            }
//            AddItem(Root, value);
//        }
//        Print(Root);
//        std::cout << "\n\n";
//        for (int i = 1; i < 10; i++) {
//            std::cout << "At level " << i << ":   " << summ_k(Root, i) - summ_k(Root, i - 1) << std::endl;
//        }
//    }
//    ~Mytree();
//
//    void Print(Tree* Root);
//    void AddItem(Tree* node, int x);
//    int  summ_k(Tree* Root, int nam);
//};
//
//
//
//Mytree::~Mytree() {}
//
//// Функция добовления элемента в дерево (Вызываеться конструктором)
//void Mytree::AddItem(Tree* node, int _x)
//{
//    if (_x < node->value)
//    {
//        if (node->Left == nullptr)
//            node->Left = new Tree(nullptr, nullptr, _x);
//        else
//            AddItem(node->Left, _x);
//    }
//    if (_x > node->value)
//    {
//        if (node->Right == nullptr)
//            node->Right = new Tree(nullptr, nullptr, _x);
//        else
//            AddItem(node->Right, _x);
//    }
//}
//
////Выводит бинарное дерево 
//void Mytree::Print(Tree* Root) {

    if (!Root)return;

    tabs += 5;

    Print(Root->Right);
    for (int i = 0; i < tabs; i++) std::cout << " ";
    std::cout << Root->value << std::endl;
    Print(Root->Left);

    tabs -= 5;

    return;
}

//Подсчитывает количесво элементов на уровне 
int Mytree::summ_k(Tree* Root, int nam) {

    int sum = 0;

    if ((Root != NULL) && (nam > 0)) {
        sum += summ_k(Root->Left, nam - 1);

        sum++;

        sum += summ_k(Root->Right, nam - 1);
    }
    return sum;
};
//начало
int main() {
    Mytree ls;
    return 0;
}
