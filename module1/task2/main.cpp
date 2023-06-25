// Дан отсортированный массив различных целых чисел A[0..n-1] и массив целых чисел B[0..m-1]. Для каждого элемента массива B[i] 
// найдите минимальный индекс элемента массива A[k], ближайшего по значению к B[i].
// Требования: Время работы поиска для каждого элемента B[i]: O(log(k)). Внимание! В этой задаче для каждого B[i] сначала нужно 
// определить диапазон для бинарного поиска размером порядка k с помощью экспоненциального поиска, а потом уже в нем делать бинарный поиск.


#include <iostream>
using namespace std;

int binary_search( const int* arr, int first, int last, int element );
int exponential_search(int arr[], int arr_len, int target);
int find_res(int arr[], int target, int arr_len);


int main(){
    // заполняем А
    int n;
    cin >> n;
    int* A = new int[n];
    for(int i = 0; i < n; i++) {
        cin >> A[i];
    }
    // заполняем В
    int m;
    cin >> m;
    int* B = new int[m];
    for(int i = 0; i < m; i++) {
        cin >> B[i];
    }
    // выводим результат для каждого B[i]
    for(int i = 0; i < m; i++){
      cout << find_res(A, B[i], n) << " ";
    }
    delete []A;
    delete []B;
    return 0;
}

//бинарный посиск в полученном диапазоне, врзвращаем ближайший к искомому элемент(из двух соседних)
int binary_search( int arr[], int first, int last, int target ){
  while( first < last - 1 ) {
    int mid = ( first + last ) / 2;
    if( arr[mid] < target)
      first = mid;
    else
      last = mid;
  }
  if(first == last && first > 0) {
        first--;
  }
  return (arr[last] - target >= target - arr[first]) ? first : last;
}

//ищем нужный диапазон эксп. поиском, в нем вызываем бинарный поиск
int exponential_search(int arr[], int arr_len, int target) {
    if (arr[0] == target)
        return 0;

    int i = 1;
    while (i < arr_len && arr[i] <= target)
        i *= 2;
    return binary_search(arr, i/2, min(i, arr_len-1), target);
}

int find_res(int arr[], int target, int arr_len){
    if(target < arr[0]) {  // если искомый элемент, меньше чем самый маленький элемент, то ответ - самый маленький элемент
        return 0;
    }
    if(target > arr[arr_len - 1]) {  // если искомый элемент, больше чем самый большой элемент, то ответ - самый большой элемент
        return arr_len - 1;
    }
    return exponential_search(arr, arr_len,target);
}    