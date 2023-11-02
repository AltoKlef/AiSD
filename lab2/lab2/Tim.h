#pragma once
#include "DinArr.h"
#include <algorithm>

template<typename T>
void output(DinArr<T> arr) {//вывод элементов
	for (int i = 0; i < arr.size(); i++) {
		//cout <<"arr["<<i<<"]= "<< arr[i] << " ";
        cout << arr[i] << " ";
	}
}
template<typename T>
void output(DinArr<T> arr,int first,int last) {//вывод в заданном диапазоне
	for (int i = first; i < last; i++) {
		cout << arr[i] << " ";
	}
	cout << "\n\n\n";
}
int GetMinrun(int n) {//получение minrun
    int r = 0;
    while (n >= 64) {
        r |= (n & 1);
        n >>= 1;
    }
    return n + r;
}
template <typename T>
void InsertionSort(DinArr<T>&arr, int left, int right)//классическая сортировка вставками 
{
	for (int i = left + 1; i <= right; i++) {
		int temp = arr[i];
		int j = i - 1;
		while (j >= left && arr[j] > temp) {
			arr[j + 1] = arr[j];
			j--;
		}
		arr[j + 1] = temp;
	}
}

template <typename T>
void merge(DinArr<T>& arr, int left, int mid, int right) {//модернизированное слияние 
    int len1 = mid - left + 1;
    DinArr<T> leftArr(len1);//создается массив для левой части

    for (int i = 0; i < len1; i++) { //массив заполняется от left до mid
        leftArr[i] = arr[left + i];
    }
    int i = 0, j = mid+1;
    int k = left;
    int leftcount=0;//счетчики для подсчета количества элементов подряд взятых из какого-то массива
    int rightcount=0;
    while (i < len1 && j <= right) {
        if (leftArr[i] <=arr[j]) {
            arr[k] = leftArr[i];
            i++;
            leftcount++;
            rightcount = 0;
        }
        else {
            arr[k] = arr[j];
            j++;
            rightcount++;
            leftcount = 0;
        }
        k++;
        if (leftcount >= 7) { //так называемый галоп если из левого массива берут много элементов подряд
            leftcount = 0;
            int stepen = 0;
            for (int ii = i + pow(2, stepen); ii< len1;ii=ii+pow(2,stepen)) {
                if (leftArr[ii] < arr[j]) {
                    cout << " " << "ii =  " << ii;
                    stepen++;
                }
                else {
                    stepen--;
                    ii = i + pow(2, stepen);
                    while (i < ii) {
                        arr[k] = leftArr[i];
                        i++;
                        k++;
                    }
                    break;
                }
            }
        }
        if(rightcount >= 7) { //галоп в случае если правый массив (аналогично)
            rightcount = 0;
            int stepen = 0;
            for (int jj = j + pow(2, stepen); jj< right;jj=jj+pow(2,stepen)) {
                if (arr[jj] < arr[j]) {
                    stepen++;
                }
                else {
                    stepen--;
                    jj = j + pow(2, stepen);
                    while (j < jj) {
                        arr[k] = leftArr[j];
                        j++;
                        k++;
                    }
                    break;
                }
            }
        }
        
    }
    //прицепляем остаток 
    while (i < len1) {
        arr[k] = leftArr[i];
        i++;
        k++;
    }

    while (j < right) {
        arr[k] = arr[j];
        j++;
        k++;
    }
}
template <typename T>
void timSort(DinArr<T>& arr,int n) {
    int minrun = GetMinrun(n);
	//cout << "minrun is:" << minrun << endl;
	for (int i = 0; i < n; i += minrun) {
		InsertionSort(arr, i, min((i + minrun - 1), n-1));//разбиение на подмассивы и сортировка их
	}
    for (int size = minrun; size < n; size = 2 * size) {
        for (int left = 0; left < n; left += 2 * size) {
            int mid = min((left + size - 1), (n-1));
            int right = min((left + 2 * size - 1), n-1);

            if (mid < right) {
                merge(arr, left, mid, right);//слияние массивов
            }
        }
    }
}
