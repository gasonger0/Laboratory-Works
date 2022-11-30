#pragma once
#include <iostream>

struct Node {
	int value{};
	Node* next{ nullptr };
};

class List {
protected:
	Node* head;
public:
	List() {};
	List(char* buf) {
		int i{ 0 };
		if (buf != nullptr) {
			while (buf[i] != NULL) {
				insert(static_cast<int>(buf[i]));
				i++;
			}
		}
	}



	void insert(int val) {
		Node* new_p = new Node;
		new_p->value = val;
		if (head == NULL) {
			head = new_p;
			return;
		}
		else {
			Node* cur = head;
			while (cur->next != NULL) {

				cur = cur->next;

			}
			cur->next = new_p;

			return;
		}
	}

	void print() {

		Node* cur = head;

		while (cur != NULL) {

			std::cout << cur->value << ' ';

			cur = cur->next;

		}
		std::cout << std::endl;
	}

	void erase(Node* t) {
		if (head == NULL) {

			return;
		}
		if (head->value == t->value) {

			Node* a = head;

			head = a->next;

			delete a;

		}
		if (head != NULL) {

			Node* cur = head->next;

			Node* prev = head;

			while (cur != NULL && cur->next != NULL) {

				if (cur->value == t->value) {

					cur = cur->next;

					prev->next = cur;

					continue;
				}
				cur = cur->next;

				prev = prev->next;

			}
			if (cur == NULL) {

				return;
			}
			else if (cur->next == NULL) {

				if (cur->value == t->value) {

					prev->next = nullptr;

					cur = NULL;

				}
			}
		}
		else {

			return;
		}
	}

	Node* operator[] (const int index) {

		Node* cur = head;

		int i{ 0 };

		while (i < index && cur != NULL) {

			cur = cur->next;

			i++;

		}
		return cur;
	}
};
