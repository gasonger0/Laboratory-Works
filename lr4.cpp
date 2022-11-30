#include <iostream>

const int SIZE{3};                                                              // ���������, ������� ������

struct Leaf{                                                                    // ��������� ������
    unsigned short number{};                                                    // ����� �����
    unsigned short sizeOfChild{};                                               // ���������� ��������
    Leaf **child;                                                               // ��������� �� ������ ��������
    
    Leaf(unsigned short n = 0) : number(n), sizeOfChild(0),                     // ������������ ������
        child(new Leaf* [SIZE]) {                                               // ����� ����� - �� ��������� ������������
        for (int i = 0; i < SIZE; i++) child[i] = 0;                            // ����� - SIZE, ��� - ����
    }
};

class Treehouse{                                                                // ����� �������� ������
private:
    Leaf* root{ nullptr };                                                      // ������ ������, ������
public:

    Treehouse(){                                                                // ����������� ������
        addLeaf(root);                                                          // ������������� ������� �����
        unsigned short lvl{};                                                   // ������� ������ (������)
        std::cout << "Enter level of Leaf: ";                                   // ����������� �� ����
        try {                                                                   // ���� ������ ������ � ����������� ���������� 
            std::cin >> lvl;
            std::cin.clear();
        }
        catch (std::exception e) {
            std::cout << "Enter correct values (positive int)\n";
        }
        int curLvl{};                                                           // �������� � ������������ ���� �������� ������ ������
        for (int i{}; i < lvl; i++) {                                           // ���� �� ����� �� ������� ������
            curLvl++;                                                           // ����������� ������� �� 1, �������� � 1
            std::cout << "Filling level " << curLvl << ":\n";                   // ��������� � ������� ������
            addLeaf(root);                                                      // ���������, ������� � �����
        }
    }

    ~Treehouse() {                                                              // ����������
        delete root;                                                            // ������� ������ ������
    }

    void addLeaf(Leaf *&T){                                                     // ����� ���������� ����� � ������, �� ���� ��������� ��������� �� ����
        if (!T) {                                                               // ���� ���� �� ����������
            unsigned short value;                                               // ����� �������� �����
            std::cout << "Enter number of Leaf: ";                              // ����������� �� ���� ������ �����
            try {                                                               // ���� ������
                std::cin >> value;
                std::cin.clear();                                               // ������ �������� ������
            }
            catch (std::exception e) {                                          // ��������� ����������
                std::cout << "Enter correct numbers! (int)\n";
            }
            T = new Leaf(value);                                                // �������� ������ ��� ����, �������������� (����� ������������ ���������)
            while (true) {
                std::cout << "Enter num of sons: ";                             // ����������� �� ���� ���������� ��������
                try {                                                           // ���� ���������� ��������
                    std::cin >> T->sizeOfChild;
                    std::cin.clear();                                           // ������ ������ �����
                }
                catch (std::exception e) {                                      // ��������� ����������
                    std::cout << "Enter correct value (positive integer)\n";
                }
                if (T->sizeOfChild > SIZE) {                                    // ���� ���������� ������� ������ ����������������                                         
                    std::cout << "Max count of tree-child "                     // ������ � ������
                        << SIZE << ". Retry.\n";
                }
                else {
                    break;
                }
            }
        }else{                                                                  // �����, ���� ���� ���������������
            for(int i{}; i < T->sizeOfChild; i++){                              // �������� �� ��� ��������
                addLeaf(T->child[i]);                                           // �������� ��������� ��
            }
        }
    }

    int findHeight(int height, Leaf *&T, int level = 0){                        // ������� ������ ������� ��������� ������, �� ���� ��������� ������,
                                                                                // �� ������� ����� ������, ���� � ������� �������
        int counter{ 0 };                                                       // ������� ������� �� �������� ������
        if (T != nullptr) {                                                     // ���� ���� �� ����
            if (level == height) {                                              // ���� ������ ����� ������� � ��������
                counter++;                                                      // ����������� �������
            }
            if (level < height) {                                               // ���� ���� ���� �������� ������
                if (T->sizeOfChild != 0) {                                      // ���� � ����� ���� �������
                    for (int i{}; i < T->sizeOfChild; i++) {                    // �������� �� ��������
                        counter += findHeight(height, T->child[i], ++level);    // ���� ����� ��� ����� �������� ������, ������� ������� ��������� �� 1
                    }
                }
            }
        }
        return counter;                                                         // ���������� ���������� ���������� �������
    }

    int startSearch(){                                                          // ������� ������ ������ 
        int counterMain{}, height{};                                            // ������� ������� � ������, �� ������� ������
        std::cout << "Enter search-level: ";                                    // ����������� �� ���� ������
        try{
            std::cin >> height;
        }catch(std::exception e){                                               // ���������� ����������
            std::cout << "Enter correct values (positive integers)";
        }
        if(root->child != nullptr){                                             // ���� � ����� ���� ������
            for(int i{}; i < root->sizeOfChild; i++){                           // �������� �� ���
                counterMain += findHeight(height, root->child[i], 0);           // ���������� �������� ������
            }
        }
        return counterMain;                                                     // ���������� �������
    }
};

int main(){
    Treehouse alpha;
    std::cout << alpha.startSearch();
    return 0;
}