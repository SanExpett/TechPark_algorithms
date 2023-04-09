// Вернуть значение бита в числе N по его номеру K.

#include <iostream>
using namespace std;

int bit(unsigned int , int);

int main(int, char**) {
    int n, k, res;
    cin >> n >> k;
    res = bit(n, k);
    cout << res << endl;
    return 0;
}

int bit(unsigned int num, int pos){ //сдвигаем на pos бит вправо, умножаем на 1(смотрим младший бит)
    return (num >> pos) & 1;
}
