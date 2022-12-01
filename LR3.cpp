#include <iostream>

struct Tree {
	int value{};																					// Номер листа
	Tree* left{};																					// Потомок слева
	Tree* right{};																					// Потомок справа

	Tree(int _) : value(_), left(nullptr), right(nullptr) {};										// Конструктор с передачей в него значения листа
	Tree() : value{}, left(nullptr), right(nullptr) {};												// Конструктор по умолчанию
};

int compareByStruct(Tree* a, Tree* b, int lvl_a, int lvl_b, int cur_lvl_a, int cur_lvl_b) {			// Сравнение по структуре: принимает на вход
																									// Сравниваемые поддеревья, их уровни и текущий уровень
	int out{};																						// Переменная для вывода числа совпавших деревьев
	if ((lvl_a <= cur_lvl_a) && (lvl_b <= cur_lvl_b)) {												// Если находимся на допустимых уровнях
		if ((a->left != NULL) == (b->left != NULL)) {												// Если "пустота" листьев совпадает слева
			if ((a->right != NULL) == (b->right != NULL)) {											// Если "пустота" листьев совпадает справа
				out += compareByStruct(a->left, b->left, lvl_a, lvl_b, cur_lvl_a + 1, cur_lvl_b + 1);	// Сравниваем с увеличением уровня
				out += compareByStruct(a->right, b->right, lvl_a, lvl_b, cur_lvl_a + 1, cur_lvl_b + 1);
			}
		}
	}
	return out;
}

int compareByVal(Tree* a, Tree* b) {																// Сравнение по значению
	int match{};
	if ((a->left != nullptr) && (b->left != nullptr)) {
		if ((a->left->value) == (b->left->value)) {
			match++;
			match += compareByVal(a->left, b->left);
		}
	}

	if ((a->right != nullptr) && (b->right != nullptr)){
		if ((a->right->value) == (b->right->value)) {
			match++;
			match += compareByVal(a->right, b->right);
		}
	}

	return match;
}

int CompareT(Tree* a, Tree* b) {
	if (a->left && !b->left) return 0;
	if (a->right && !b->right) return 0;
	return (!a->left || CompareT(a->left, b->left)) && (!a->right || CompareT(a->right, b->right));
}

class Treehouse {

	friend int compare(Treehouse a, Treehouse b) {													// Функция сравнения
		int match{};
		match += CompareT(a.bin->left, b.bin->left);
		match += CompareT(a.bin->right, b.bin->right);
		return match;
	}												
private:
	Tree* bin = new Tree(0);																		// Наше дерево			
public:

	int level{};																					// Уровень дерева

	Treehouse() {																					// Конструктор														
		std::cout << "Enter level of Tree: ";														// Ввод ранга дерева
		try {
			std::cin >> level;
			std::cin.clear();
		}
		catch (std::exception e) {
			std::cout << "Enter integers!!!";
		}
		for (int i{}; i < level; i++) {																// Проходим к нижнему уровню дерева
			add(bin->left);																			// Добавляем потомков слева 
			add(bin->right);																		// Добавляем потомков справа
		}
	}

	void add(Tree*& T) {																			// Втсавка потомков, на вход принимает лист, в который нужно вставить потомков
		int value{};																				// Значение для вставки
		if (!T) {																					// Если переданный лист пуст
			std::cout << "Enter value of cell: ";													// Вводим значение
			try {
				std::cin >> value;
				std::cin.clear();
			}
			catch (std::exception e) {
				std::cout << "Enter correct value! (int)\n";
			}
			if (value != 0) {
				T = new Tree(value);																// Записываем новое значение
			}
		}
		else {																						// Если лист не пустой
			add(T->left);																			// Вставляем потомков
			add(T->right);
		}
	}

	void print(Tree* root) {
		if (root == nullptr) {
			return;
		}
		std::cout << root->value << " ";
		print(root->left);
		print(root->right);

	}

	void print_start() {
		std::cout << bin->value << " ";
		print(bin->left);
		print(bin->right);
	}
};




	

int main(){
	Treehouse alpha;
	Treehouse beta;
	alpha.print_start();
	std::cout << std::endl;
	beta.print_start();
	std::cout << std::endl << std::endl;
	std::cout << compare(alpha, beta);
	return 0;
}
