#include <iostream>
#include <conio.h>
#include <cmath>
#include <string>
#include <sstream>
using namespace std;
class OutOfBoundsException : public runtime_error {
public:
	OutOfBoundsException(const string& message) : runtime_error(message) {
		cerr << message;
	}
};
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
		if (index >= 0 && index < length) {
			return get_index(index);
		}
		else {
			throw OutOfBoundsException("Error: the index goes beyond the list");
		}
	}
	int get_length() {
		return length;
	}


	T insert(int index, T data) {//добавить по индексу
		if (index >= 0 && index < length){
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
		return ptr->data;}
		else {
			throw OutOfBoundsException("Error: the index goes beyond the list");
		}
	}
	void erase(int index) {//удалить по индексу
		if (index >= 0 && index < length) {
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
		else {
			throw OutOfBoundsException("Ошибка: Индекс выходит за пределы списка.");
		}
	}
	void erase_this(const T& value) {//удаляет все узлы с data равным value
		Node<T>* current = head;
		int index = 0;
		while (index<length && current!=NULL) {
			if (current->data == value) {
				Node<T>* ptr = get_node(index);
				if (ptr->prev == NULL) {
					current = ptr->next;
					delete_first();
				}

				else if (ptr->next == NULL) {
					delete_last();
				}
				else{
					Node<T>* left = ptr->prev;
					Node<T>* right = ptr->next;
					left->next = right;
					right->prev = left;
					length--;
					current = ptr->next;
					delete ptr;
				}
				
			}
			else {
				current = current->next;
				index++;
			}
		}
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
template <class T>
class DinArr {
private:
	int capacity; // Размер массива
	int length;   // Текущее количество элементов
	T* arr;       // Динамический массив
public:
	DinArr() {
		length = 0;
		capacity = 20; //20 будет магическим числом
		arr = new T[capacity];
	}

	DinArr(int initialSize) {
		length = initialSize;
		capacity = length + 20;
		arr = new T[capacity];
	}

	~DinArr() {
		delete[] arr;
	}

	T& operator[](int index) {
		if (index >= 0 && index < length) {
			return arr[index];
		}
		else {
			throw OutOfBoundsException("Error: accessing uninitialized memory");
		}
		
	}
	void push_back(const T& value) {

		if (length >= capacity) {
			// Увеличиваем размер массива, если не хватает места
			capacity += 20;
			T* temp = new T[capacity];// временный массив
			for (int i = 0; i < length; i++) {
				temp[i] = arr[i];
			}
			delete[] arr;//уадляем прошлую версию массива
			arr = temp;
			arr[length] = value;
			length++;		   
		}
		else {
			arr[length] = value;
			length++;
		}
	}
	void add(int index, const T& value) {
		if (index >= 0 && index < length) {
			if (length >= capacity) {
				capacity += 20;
				T* temp = new T[capacity];
				for (int i = 0; i < length; i++) {
					temp[i] = arr[i];
				}
				delete[] arr;
				arr = temp;
			}
			// Сдвигаем элементы вправо
			for (int i = length; i > index; i--) {
				arr[i] = arr[i - 1];
			}
			arr[index] = value;
			length++;
		}
		else {
			throw OutOfBoundsException("Error: accessing uninitialized memory");
		}
	}
	void remove(int index) {
		if (index >= 0 && index < length) {
			for (int i = index; i < length - 1; i++) {
				arr[i] = arr[i + 1];
			}
			length--;
		}
		else {
			throw OutOfBoundsException("Error: accessing uninitialized memory");
		}
	}
	// Получение текущей длины массива
	int size() const {
		return length;
	}
};
// Проверка, является ли символ оператором
bool isOperator(const string& token) {
	return token == "+" || token == "-" || token == "*" || token == "/" || token == "^";
}

// Проверка, является ли символ функцией
bool isFunction(const string& token) {
	return token == "sin" || token == "cos";
}

// Определение приоритета оператора
int getPrecedence(const string& token) {
	if (token == "+" || token == "-") return 1;
	if (token == "*" || token == "/") return 2;
	if (token == "^") return 3;
	return 0; // Для функций и чисел
}

// Преобразование инфиксного выражения в обратную польскую запись
//используется двусвязный список в качестве стека
DinArr<string> infixToRPN(const string& infixExpression) {
	istringstream iss(infixExpression);
	List<string> operators; //будет нашим стеком
	DinArr<string> output; // будет чисто хранить выходные данные
	string token;
	while (iss >> token) {
		if (token == "(") {
			operators.add_last(token);
		}
		else if (token == ")") { //по поводу записи operators[operators.get_length() - 1] 
			//- это эквивалентно функции top в обычном стеке где мы просто смотрим на самый последний элемент
			while (operators.get_length() != 0 && operators[operators.get_length() - 1] != "(") {
				output.push_back(operators[operators.get_length() - 1]);
				operators.delete_last();
			}
			operators.delete_last(); // Удаляем открывающую скобку
		}
		else if (isOperator(token)) {
			while (operators.get_length() != 0 && isOperator(operators[operators.get_length() - 1]) &&
				getPrecedence(token) <= getPrecedence(operators[operators.get_length() - 1])) {
				output.push_back(operators[operators.get_length() - 1]);
				operators.delete_last();
			}
			operators.add_last(token);
		}
		else if (isFunction(token)) {
			operators.add_last(token);
		}
		else {
			output.push_back(token); // Элемент - число
		}
	}

	while (operators.get_length() != 0) {
		output.push_back(operators[operators.get_length() - 1]);
		operators.delete_last();
	}

	return output;
}
void testspisok() {
	system("cls");
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
	lst.add_first("Поперчить");
	lst.add_last("Поперчить");
	lst.insert(2, "Поперчить");
	lst.insert(3, "Добавить масла");
	lst.insert(4, "Поперчить");
	for (int i = 0; i < lst.get_length(); i++) {
		cout << "lst[" << i << "] = " << lst[i] << endl;
	}
	cout << "Длина списка: " << lst.get_length() << endl;
	cout << "О нет, мы все испортили" << endl << endl;


	cout << "Вернем на место" << endl;
	lst.erase(3);
	lst.erase_this("Поперчить");
	for (int i = 0; i < lst.get_length(); i++) {
		cout << "lst[" << i << "] = " << lst[i] << endl;
	}
	cout << "Длина списка: " << lst.get_length() << endl;
	cout << "Получилось!" << endl << endl;
}
void testmassiv() {
	system("cls");
	DinArr<short> arr;
	cout << "Тестируем массив" << endl;
	cout << "Длина массива:" << arr.size() << endl;
	int num = 42;
	arr.push_back(num);
	arr.push_back(27);
	arr.push_back(1337);
	for (int i = 0; i < arr.size(); i++) {
		cout << "arr[" << i << "] = " << arr[i] << endl;
	}
	cout << "Длина массива:" << arr.size() << endl;
	cout << endl << "Добавим элемент на 1 позицию" << endl;
	arr.add(1, 78);
	for (int i = 0; i < arr.size(); i++) {
		cout << "arr[" << i << "] = " << arr[i] << endl;
	}
 	cout << "Длина массива:" << arr.size() << endl;
	//arr.add(9, 3);//если расскоментировать строку то можно вызвать предусмотренное в классе исключение
	cout << endl << "Удаляем элемент 2" << endl;
	arr.remove(2);
	for (int i = 0; i < arr.size(); i++) {
		cout << "arr[" << i << "] = " << arr[i] << endl;
	}
	cout << "Длина массива:" << arr.size() << endl;
	cout << "Ха-ха, забавно получилось '':3''"<<endl;

}
void teststack() {
	system("cls");
	string infixExpression = "3 + 2 * ( 1 - sin ( 4 ^ 2 ) ) / 2 + cos ( 3 )";
  	cout << "Тестовая инфиксная строка: " << infixExpression<<endl;
	DinArr<string> rpnExpression = infixToRPN(infixExpression);
	cout << "Обратная польская запись: ";
	for (int i = 0; i < rpnExpression.size(); i++) {
		cout << rpnExpression[i] << " ";
	}
	cout<<endl<<"Введите собственную строку: ";
	getline(cin,infixExpression);
	rpnExpression = infixToRPN(infixExpression);
	cout << "Вот ваша строка в обратной польской записи: " << endl;
}

int main()
{
	setlocale(LC_ALL, "ru");
	testspisok(); 
	cout << "Нажмите любую кнопку чтобы продолжить";
	char m=_getch();
	testmassiv();
	cout << "Нажмите любую кнопку чтобы продолжить";
	m = _getch();
	teststack();
	

	
	return 0;
}