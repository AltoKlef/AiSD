#include <iostream>
#include <stdlib.h> // нужен для вызова функций rand(), srand()
#include <time.h> // нужен для вызова функции time()
#include "Tim.h"
using namespace std;

// Функция генерирования случайного целочисленного числа в указанных пределах.
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
void check(DinArr<int> arr) {
    int size = arr.size();
    cout << endl<<"Wrong numbers:"<<endl;
    
    for (int i = 1; i < size; i++) {
        if (arr[i] < arr[i - 1]) {
            cout <<"arr[" <<i<<"] =" << " " << arr[i] << endl;
            cout << "arr[" << i-1 << "] =" << " " << arr[i-1] << endl;
        }
    }
}
int main()
{
    //я не стал делать интерфейс ибо особого смысла нет (не будете же вы вводить вручную 1399229 элементов?)
    srand(time(NULL));
    DinArr<int> array(1000000);//создаем массив размером 1000000 (для тестов можно сделать меньше)
    randomfill(array, array.size(), 1, 1000);//1 и 1000 пределы случайных чисел 
    //output(array);
    timSort(array,array.size());
   // output(array); 
   check(array);//эта функция проверяет вручную расстановку элементов массива и выводит неправильные номерат (если есть)
   system("pause");
   system("cls");
   DinArr<int> arr(200); //тут более показательно на массиве 200 элементов с выводом
   randomfill(arr, arr.size(), 1, 1000);
   cout << "Unsorted arr:" << endl;
   output(arr);
   timSort(arr, arr.size());
   cout <<endl<< "Sorted arr:" << endl;
   output(arr); 
   check(arr);
}
