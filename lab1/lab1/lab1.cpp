#include <iostream>
#include <cmath>
#include <string>
#include <sstream>
using namespace std;
class OutOfBoundsException : public runtime_error {
public:
	OutOfBoundsException(const string& message) : runtime_error(message) {
		cerr << message;
	}
};//это прикол


//узел и список
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
	List(const List<T>& other) { //конструктор копирования
		head = tail = NULL;
		length = 0;

		// Копируем элементы из другого списка
		Node<T>* current = other.head;
		while (current != NULL) {
			add_last(current->data);
			current = current->next;
		}
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
		if (tail == NULL) {
			return;
		}

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
		if (index >= 0 && index < length) { //arr[2]="2"
			return get_index(index);//get_index =  ptr->data 
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
	T top() { //в большей мере для упрощения обращения к стеку
		return tail->data;
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

//

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
	DinArr(const DinArr<T>& other) {
		length = other.length;
		capacity = other.capacity;
		arr = new T[length];

		for (int i = 0; i < length; i++) {
			arr[i] = other.arr[i];
		}
	}
	DinArr<T>& operator=(const DinArr<T>& other) {
		if (this == &other) {
			return *this; // Самоприсваивание, ничего делать не нужно
		}

		// Очищаем текущий массив
		delete[] arr;

		// Копируем размер
		length = other.length;

		// Выделяем память для нового массива
		arr = new T[length];

		// Копируем элементы из другого массива в этот
		for (int i = 0; i < length; i++) {
			arr[i] = other.arr[i];
		}

		return *this; // Возвращаем *this, чтобы позволить цепочку присваиваний
	}
	

	T& operator[](int index) {
		if (index >= 0 && index < length) {
			return (arr[index]);
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
	~DinArr() {
		delete[] arr;
	}
};



//

//тут все что связано с алгоритмом сортировки и обратным
bool isNumber(const string& str) {
	for (char c : str) {
		if (!isdigit(c) && c!='.' && c!=',') {
			return false; // Если хотя бы один символ не является цифрой, это не число
		}
	}
	return true; // Все символы - цифры, это число
}
bool isFunction(const string& token) {
	return token == "sin" || token == "cos";
}
bool isOperator(const string& token) {
	return token == "+" || token == "-" || token == "*" || token == "/" || token == "^";
}
// Определение приоритета оператора
int getPrecedence(const string& token) {
	if (token == "+" || token == "-") return 1;
	if (token == "*" || token == "/") return 2;
	if (token == "^") return 3;
	return 0; 
}


DinArr<string> sort_algorythm(string expression) { //та самая магическая польская сортировка
	istringstream iss(expression);
	List<string> stack; //будет нашим стеком
	DinArr<string> output; // будет чисто хранить выходные данные очередь вывода типо
	string token;
	while (iss >> token) {
		if (isNumber(token)) {
			output.push_back(token);
		}
		else if (isFunction(token)) {
			stack.add_last(token);
		}
		else if(isOperator(token)){
			while (stack.get_length() != 0 &&(getPrecedence(stack.top()) >= getPrecedence(token))) {
				output.push_back(stack.top());
				stack.delete_last();
			}
			stack.add_last(token);
		}
		else if (token == "(") {
			stack.add_last(token);
		}
		else if (token == ")") {
			while (stack.top() != "(") {
				output.push_back(stack.top());
				stack.delete_last();
				if (stack.get_length() == 0) {
					throw OutOfBoundsException("Ошибка: В выражении пропущена скобка");
				}
			}
			stack.delete_last();
			if (isFunction(stack.top())) {
				output.push_back(stack.top());
				stack.delete_last();
			}
		}
	}
	while (stack.get_length() != 0 && isOperator(stack.top())) {
		if (stack.top() == "(") {
			throw OutOfBoundsException("Ошибка: В выражении пропущена скобка");
		}
		output.push_back(stack.top());
		stack.delete_last();
	}
	return output;
}

double calculator(DinArr<string> polska) { //тут обратно из польской записи в число нормальное
	List<double> stack;
	string token;
	for (int i = 0; i < polska.size();i++) {
		token = polska[i];
		if (isNumber(token)) {
			// Если элемент - число, помещаем его в стек
			stack.add_last(atof(token.c_str())); 
			// единственный момент кода который я не понимаю. функция atof округляет число если оно было дробным. в меньшую сторону
		}
		//косинусам отдельное приглашение
		else if (isFunction(token)) {
			double operand1 = stack.top();
			stack.delete_last();
			if (token == "cos") {
				stack.add_last(cos(operand1));
			}
			else if (token == "sin") {
				stack.add_last(sin(operand1));
			}
		}
		else {
			// Если элемент - оператор, выполняем соответствующее действие
			double operand2 = stack.top();
			stack.delete_last();
			double operand1 = stack.top();
			stack.delete_last();

			if (token == "+") {
				stack.add_last((operand1 + operand2));
			}
			else if (token == "-") {
				stack.add_last((operand1 - operand2));
			}
			else if (token == "*") {
				stack.add_last((operand1 * operand2));
			}
			else if (token == "/") {
				if (operand2 != 0) {
					stack.add_last((operand1 / operand2));
				}
				else {
					cerr << "Ошибка: деление на ноль." << std::endl;
					return 0.0;
				}
			}
			else if (token == "^") {
				stack.add_last((pow(operand1, operand2)));
			}
		}
	}

	if (stack.get_length() != 0) {
		return stack.top();
	}
	else {
		cerr << "Ошибка: неверное выражение." << std::endl;
		return 0.0;
	}
}


///  тут три функции которые и тестят функционал классов . откройте если хотите увидеть какие методы используются
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
	string infixExpression = "cos ( 3 - 4 ^ 2 ) + 19 * 3 - 2 / 2";
  	cout << "Тестовая инфиксная строка: " << infixExpression<<endl;
	DinArr < string > arr = sort_algorythm(infixExpression);
	cout << "Обратная польская запись: ";
	for (int i = 0; i < arr.size(); i++) {
		cout << arr[i]<< " ";
	}
	cout << endl<<"Результат: " << calculator(arr) << endl;
	cout<<endl<<"Введите собственную строку (отделяя каждый токен пробелом ): ";
	getline(cin,infixExpression);
	DinArr < string > arr2 = sort_algorythm(infixExpression);
	

	cout << "Обратная польская запись: ";
	for (int i = 0; i < arr2.size(); i++) {
		cout << arr2[i] << " ";
	}
	cout << endl << "Результат: " << calculator(arr2) << endl;
}

int main()
{
	// лютый интерфейс
	setlocale(LC_ALL, "ru");
	testspisok(); 
	cout << "Нажмите любую кнопку чтобы продолжить";
	//char m=_getch();
	testmassiv();
	cout << "Нажмите любую кнопку чтобы продолжить";
	//m = _getch();
	teststack();
	

	
	return 0;
}