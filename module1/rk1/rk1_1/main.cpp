
#include <iostream>

template<typename T>
int binary_search(T *arr, size_t n, T k) {
    int l = 0, r = n - 1;
    while (l <= r) {
        int m = (l + r) / 2;
        if (arr[m] == k) {
            return m;
        } else if (arr[m] < k) {
            l = m + 1;
        } else {
            r = m - 1;
        }
    }
    return l;
}

int main() {
    int n, k;
    std::cin >> n;
    int *arr = new int[n];
    for (int i = 0; i < n; i++) {
        std::cin >> arr[i];
    }
    std::cin >> k;
    std::cout << binary_search(arr, n, k) << std::endl;
    delete[] arr;
    return 0;
}