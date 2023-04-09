#include <iostream>
#include <algorithm>

template<typename T>
int find_median(T* arr, int l, int r){
    int mid = l + (r - l)/2;

    if (arr[l] < arr[mid]){
        if (arr[mid] < arr[r]) 
            return mid;
        else if (arr[l] < arr[r]) 
            return r;
        else 
            return l;
    }
    else {
        if (arr[l] < arr[r]) 
            return l;
        else if (arr[mid] < arr[r]) 
            return r;
        else 
            return mid;
    }

}

template<typename T, typename Comparator>
int partition(T* arr, int l, int r, Comparator comp){
    int pivot_idx = find_median(&arr[0], l, r - 1);
    T pivot = arr[pivot_idx];

    std::swap(arr[pivot_idx], arr[r - 1]);

    int i = l;
    int j = l;

    while(j < r - 1) {
        //Если элемент не больше опорного, то меняем a[i] и a[j] местами, 
        //сдвигаем i и сдвигаем j.
        if(comp(arr[j], pivot)) { 
            std::swap(arr[i], arr[j]);
            i++;
            j++;
        } else { //Если он больше опорного, то сдвигаем j.
            j++;
        }
        
    }
    std::swap(arr[i], arr[r - 1]);
    return i;
} 


template<typename T, typename Comparator>
void kth_element(T* arr, int size, int k, Comparator comp){
    int l = 0;
    int r = size;
    while(l < r){
        int m = partition(arr, l, r, comp);
        if(m == k){
            return;
        } else if(m < k){
            l = m + 1;
        } else {
            r = m;
        }
    }
}


template<typename T, typename Comparator>
void perc10_med_perc90(T* arr, int size, T* results, Comparator comp){
    T indexes[3] = {size / 10, size / 2, size * 9 / 10};
    for(int i = 0; i < 3; i++){
        int k = indexes[i];
        kth_element(&arr[0], size, k, comp);
        results[i] = arr[k];
    }
}

int main(){
    int count = 0;
    std::cin >> count;
    int arr[count];
    for(int i = 0; i < count; i++){
        std::cin >> arr[i];
    }
    int results [3];
    perc10_med_perc90(&arr[0], count, &results[0], [](const int& l, const int& r){
        return l <= r;
    });
    for (int i = 0; i < 3; i++){
        std::cout << results[i] << std::endl;
    }
    return 0;
}