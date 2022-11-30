#include <iostream>

const int SIZE{3};                                                              // Константа, уровень дерева

struct Leaf{                                                                    // Структура дерева
    unsigned short number{};                                                    // Номер листа
    unsigned short sizeOfChild{};                                               // Количество потомков
    Leaf **child;                                                               // Указатель на массив потомков
    
    Leaf(unsigned short n = 0) : number(n), sizeOfChild(0),                     // Конуструктор дерева
        child(new Leaf* [SIZE]) {                                               // Номер листа - из аргумента конструктора
        for (int i = 0; i < SIZE; i++) child[i] = 0;                            // Детей - SIZE, все - нули
    }
};

class Treehouse{                                                                // Класс текущего дерева
private:
    Leaf* root{ nullptr };                                                      // Корень дерева, пустой
public:

    Treehouse(){                                                                // Конструктор дерева
        addLeaf(root);                                                          // Инициализация пустого корня
        unsigned short lvl{};                                                   // Уровень дерева (высота)
        std::cout << "Enter level of Leaf: ";                                   // Приглашение на ввод
        try {                                                                   // Ввод высоты дерева с обработокой исключения 
            std::cin >> lvl;
            std::cin.clear();
        }
        catch (std::exception e) {
            std::cout << "Enter correct values (positive int)\n";
        }
        int curLvl{};                                                           // Создание и инициалзация нулём текущего уровня дерева
        for (int i{}; i < lvl; i++) {                                           // Пока не дошли до вершины дерева
            curLvl++;                                                           // Увеличиваем уровень на 1, начинаем с 1
            std::cout << "Filling level " << curLvl << ":\n";                   // Сообщение о текущем уровне
            addLeaf(root);                                                      // Заполняем, начиная с корня
        }
    }

    ~Treehouse() {                                                              // Деструктор
        delete root;                                                            // Удаляем корень дерева
    }

    void addLeaf(Leaf *&T){                                                     // Метод добавления листа в дерево, на вход принимает указатель на лист
        if (!T) {                                                               // Если лист не существует
            unsigned short value;                                               // Номер текущего листа
            std::cout << "Enter number of Leaf: ";                              // Приглашение на ввод номера листа
            try {                                                               // Ввод номера
                std::cin >> value;
                std::cin.clear();                                               // Чистка входного потока
            }
            catch (std::exception e) {                                          // Обработка исключения
                std::cout << "Enter correct numbers! (int)\n";
            }
            T = new Leaf(value);                                                // Выделяем память под лист, инициализируем (вызов конструктора структуры)
            while (true) {
                std::cout << "Enter num of sons: ";                             // Приглашение на ввод количества потомков
                try {                                                           // Ввод количества потомков
                    std::cin >> T->sizeOfChild;
                    std::cin.clear();                                           // Чистка потока ввода
                }
                catch (std::exception e) {                                      // Обработка исключения
                    std::cout << "Enter correct value (positive integer)\n";
                }
                if (T->sizeOfChild > SIZE) {                                    // Если количество сыновей больше предусмотренного                                         
                    std::cout << "Max count of tree-child "                     // Ошибка и повтор
                        << SIZE << ". Retry.\n";
                }
                else {
                    break;
                }
            }
        }else{                                                                  // Иначе, если лист инициализирован
            for(int i{}; i < T->sizeOfChild; i++){                              // Проходим по его потомкам
                addLeaf(T->child[i]);                                           // Пытаемся заполнить их
            }
        }
    }

    int findHeight(int height, Leaf *&T, int level = 0){                        // Функция поиска листьев заданного уровня, на вход принимает высоту,
                                                                                // до которой нужно искать, лист и текущий уровень
        int counter{ 0 };                                                       // Счётчик листьев на заданной высоте
        if (T != nullptr) {                                                     // Если лист не пуст
            if (level == height) {                                              // Если высота листа совпала с заданной
                counter++;                                                      // Увеличиваем счётчик
            }
            if (level < height) {                                               // Если лист ниже заданной высоты
                if (T->sizeOfChild != 0) {                                      // Если у листа есть потомки
                    for (int i{}; i < T->sizeOfChild; i++) {                    // Проходим по потомкам
                        counter += findHeight(height, T->child[i], ++level);    // Ищем среди них листь заданной высоты, текущий уровень поднимаем на 1
                    }
                }
            }
        }
        return counter;                                                         // Возвращаем количество подошедших листьев
    }

    int startSearch(){                                                          // Функция начала поиска 
        int counterMain{}, height{};                                            // Счётчик листьев и высота, до которой искать
        std::cout << "Enter search-level: ";                                    // Приглашение на ввод высоты
        try{
            std::cin >> height;
        }catch(std::exception e){                                               // Обрпаботка исключения
            std::cout << "Enter correct values (positive integers)";
        }
        if(root->child != nullptr){                                             // Если у корня есть листья
            for(int i{}; i < root->sizeOfChild; i++){                           // Проходим по ним
                counterMain += findHeight(height, root->child[i], 0);           // Прибавляем наёденные листья
            }
        }
        return counterMain;                                                     // Возвращаем счётчик
    }
};

int main(){
    Treehouse alpha;
    std::cout << alpha.startSearch();
    return 0;
}