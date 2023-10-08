#include <iostream>
#include <Windows.h>
using namespace std;
template <class T>
class Node {
public:
	T data;
	Node* prev, * next;
	Node(T data) { //конструктор, 
		this->data = data;
		this->prev = this->next = NULL;
	}
};
template <class T>
class List {
private:
	Node<T>* head, * tail;
	int length;
public:

	List() {
		head = tail = NULL;
		length = 0;
	}
	T add_first(T data) { //добавить в начало
		Node<T>* ptr = new Node<T>(data);
		ptr->next = head;//указатель на "прошлый" первый объект
		if (head != NULL) { //если объект впереди был, записываем новый первый объект в предыдущий  
			head->prev = ptr;
		}
		if (tail == NULL) {//если список был пустым то наш объект и голова и хвост
			tail = ptr;
		}
		length++;
		head = ptr;
		return ptr->data;
	}
	T add_last(T data) {                     //аналогично
		Node<T>* ptr = new Node<T>(data);
		ptr->prev = tail;
		if (tail != NULL)
			tail->next = ptr;
		if (head == NULL)
			head = ptr;
		tail = ptr;
		length++;
		return ptr->data;
	}
	void delete_first() {
		if (head == NULL) return; //если пусто то скип

		Node<T>* ptr = head->next; //2 элемент
		if (ptr != NULL)//если второй элемент был, то стираем в нем указатель на первый
			ptr->prev = NULL;
		else
			tail = NULL;

		delete head;//забываем про предыдущий первый
		head = ptr;
		length--;
	}


	void delete_last() {//аналогично
		if (tail == NULL) return;

		Node<T>* ptr = tail->prev;
		if (ptr != NULL)
			ptr->next = NULL;
		else
			head = NULL;

		delete tail;
		tail = ptr;
		length--;
	}
	T get_index(int index) {
		Node<T>* ptr;
		int n;
		if (index >= length / 2) {//если индекс больше чем половина длина списка то считаем с конца
			ptr = tail;
			n = length - 1;
			while (n != index) {
				ptr = ptr->prev;
				n--;
			}
		}
		else {
			ptr = head;
			n = 0;
			while (n != index) {
				ptr = ptr->next;
				n++;
			}
		}
		return ptr->data;
	}

	T operator [] (int index) { //перегрузим скобки
		return get_index(index);
	}
	int get_length() {
		return length;
	}

	T insert(int index, T data) {//добавить по индексу
		Node<T>* right = get_node(index);
		if (right == NULL) {
			return add_last(data);
		}

		Node<T>* left = right->prev;
		if (left == NULL) {
			return add_first(data);
		}

		Node<T>* ptr = new Node<T>(data);

		ptr->prev = left;
		ptr->next = right;
		left->next = ptr;
		right->prev = ptr;
		length++;
		return ptr->data;
	}
	void erase(int index) {//удалить по индексу
		Node<T>* ptr = get_node(index);
		if (ptr == NULL)
			return;

		if (ptr->prev == NULL) {
			delete_first();
			return;
		}

		if (ptr->next == NULL) {
			delete_last();
			return;
		}

		Node<T>* left = ptr->prev;
		Node<T>* right = ptr->next;
		left->next = right;
		right->prev = left;
		length--;
		delete ptr;
	}
private:
	Node<T>* get_node(int index) { //в случае если нужен сам узел, а не данные в нем
		Node<T>* ptr;              //аналогично get_index
		int n;
		if (index >= length / 2) {
			ptr = tail;
			n = length - 1;
			while (n != index) {
				ptr = ptr->prev;
				n--;
			}
		}
		else {
			ptr = head;
			n = 0;
			while (n != index) {
				ptr = ptr->next;
				n++;
			}
		}
		return ptr;
	}
public:
	~List() { //удаляем с начала
		while (head != NULL)
			delete_first();
	}
};
//динамический массив
class LinkedList {

};
int main()
{
	setlocale(LC_ALL, "ru");
	List<string> lst;
	cout << "Тестируем строчный список" << endl;
	lst.add_first("Альбедо");
	lst.add_last("Цитринитас");
	lst.add_first("Нигредо");
	lst.add_last("Рубедо");
	for (int i = 0; i < lst.get_length(); i++) {
		cout << "lst[" << i << "] = " << lst[i] << endl;
	}
	cout << "Длина списка: " << lst.get_length() << endl;
	cout << "Великое деланье завершено" << endl << "А что если..?" << endl << endl;


	lst.insert(3, "добавить масла");
	for (int i = 0; i < lst.get_length(); i++) {
		cout << "lst[" << i << "] = " << lst[i] << endl;
	}
	cout << "Длина списка: " << lst.get_length() << endl;
	cout << "О нет, мы все испортили" << endl << endl;


	cout << "Вернем на место" << endl;
	lst.erase(3);
	for (int i = 0; i < lst.get_length(); i++) {
		cout << "lst[" << i << "] = " << lst[i] << endl;
	}
	cout << "Длина списка: " << lst.get_length() << endl;
	cout << "Получилось!" << endl << endl;
	return 0;
}