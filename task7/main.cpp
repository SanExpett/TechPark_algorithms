#include <iostream>

void count_sort(long long* arr, int n, int shift) { // стабильная сортировка подсчетом 
    long long result[n]; 
    int count[256] = {0}; 
 
    for (int i = 0; i < n; i++) 
        count[(arr[i] >> (8*shift)) & 255]++; 
 
    for (int i = 1; i < 256; i++) 
        count[i] += count[i-1]; 
 
    for (int i = n-1; i >= 0; i--) { 
        result[count[(arr[i] >> (8*shift)) & 255] - 1] = arr[i]; 
        count[(arr[i] >> (8*shift)) & 255]--; 
    } 
 
    for (int i = 0; i < n; i++) 
        arr[i] = result[i]; 
} 
 
void LSD(long long* arr, int n) { 
    for (int i = 0; i < 8; i++) // 8 байт в long long
        count_sort(arr, n, i); 
} 

int main() {
    int n;
    std::cin >> n;

    long long* arr = new long long[n];
    for (int i = 0; i < n; i++)
        std::cin >> arr[i];

    LSD(&arr[0], n);

    for (int i = 0; i < n; i++)
        std::cout << arr[i] << " ";

    delete[] arr;
    return 0;
}
