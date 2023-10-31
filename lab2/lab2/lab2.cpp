#include <iostream>
#include <stdlib.h> // нужен для вызова функций rand(), srand()
#include <time.h> // нужен для вызова функции time()
#include "Tim.h"
using namespace std;

// Функция генерирования случайного целочисленного числа в указанных пределах.
// Диапазон чисел: [min, max]
int GetRandomNumber(int min, int max)
{
    int num = min + rand() % (max - min + 1);

    return num;
}
template<typename T>
void randomfill(DinArr<T>& arr, int size, int min, int max) {
    for (int i = 0; i < size; i++) {
        arr[i] = GetRandomNumber(min, max);
    }
}
template<typename T>
void output(DinArr<T> arr) {
    for (int i = 0; i < arr.size(); i++) {
        cout << arr[i] << " ";
    }
}
int main()
{
    srand(time(NULL));
    DinArr<int> array(10);
    randomfill(array, array.size(), 1, 400);
    output(array);
    cout << "\n";
    insertion(array, array.size());
    output(array);
}
