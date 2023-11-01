#include <iostream>
#include <stdlib.h> // ����� ��� ������ ������� rand(), srand()
#include <time.h> // ����� ��� ������ ������� time()
#include "Tim.h"
using namespace std;

// ������� ������������� ���������� �������������� ����� � ��������� ��������.
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
    //� �� ���� ������ ��������� ��� ������� ������ ��� (�� ������ �� �� ������� ������� 1399229 ���������?)
    srand(time(NULL));
    DinArr<int> array(1000000);//������� ������ �������� 1000000 (��� ������ ����� ������� ������)
    randomfill(array, array.size(), 1, 1000);//1 � 1000 ������� ��������� ����� 
    //output(array);
    timSort(array,array.size());
   // output(array); 
   check(array);//��� ������� ��������� ������� ����������� ��������� ������� � ������� ������������ ������� (���� ����)
   system("pause");
   system("cls");
   DinArr<int> arr(200); //��� ����� ������������ �� ������� 200 ��������� � �������
   randomfill(arr, arr.size(), 1, 1000);
   cout << "Unsorted arr:" << endl;
   output(arr);
   timSort(arr, arr.size());
   cout <<endl<< "Sorted arr:" << endl;
   output(arr); 
   check(arr);
}
