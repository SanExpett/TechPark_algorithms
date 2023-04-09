
#include <iostream>
#include <vector>


struct Box {
    int id; 
    int x, y, z; 
    bool operator<(const Box& other) const{  // наш ящик помещается в other
        if (x <= other.x && y <= other.y && z <= other.z) {
            return true;
        }
        if (x <= other.x && z <= other.y && y <= other.z) {
            return true;
        }
        if (y <= other.x && x <= other.y && z <= other.z) {
            return true;
        }
        if (y <= other.x && z <= other.y && x <= other.z) {
            return true;
        }
        if (z <= other.x && x <= other.y && y <= other.z) {
            return true;
        }
        if (z <= other.x && y <= other.y && x <= other.z) {
            return true;
        }
        return false;
    }
};


template < typename T >
void InsertionSort( T* a, size_t n ) {
    for( int i = 1; i < n; ++i ) {
        T tmp = a[i]; // Запомним, т.к. может перезаписаться.
        int j = i - 1;
        for( ; j >= 0 && tmp < a[j]; --j ) {
            a[j + 1] = a[j];
        }
        a[j + 1] = tmp;
    }
}

int main() {
    int n;
    std::cin >> n;
    Box boxes[n];
    for (int i = 0; i < n; i++) {
        boxes[i].id = i;
        std::cin >> boxes[i].x >> boxes[i].y >> boxes[i].z;
    }
    InsertionSort(&boxes[0], n); 

    for (int i = 0 ; i < n ; i++){
        std::cout << boxes[i].id << " ";
    }
    return 0;
}