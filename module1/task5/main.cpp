#include <iostream>
#include <cstring>

template<typename T>
struct DefaultComparator {
    bool operator() (const T& l, const T& r) const {
        return l < r;
    }
};

template<typename T , typename Comparator=DefaultComparator<T>>
void merge(T* arr, T* left, size_t left_len, T* right, size_t right_len,
        Comparator comp=Comparator()) {
    
    int i = 0, j = 0, k = 0;
    while (i < left_len && j < right_len) {
        if (comp(left[i], right[j])) {
            arr[k++] = left[i++];
        } else {
            arr[k++] = right[j++];
        }
    }
    while (i < left_len) {
        arr[k++] = left[i++];
    }
    while (j < right_len) {
        arr[k++] = right[j++];
    }
}

template< typename T, typename Comparator=DefaultComparator<T> >
void MergeSort( T* arr, size_t arrLen, Comparator comp=Comparator() ){
    if( arrLen <= 1 ) {
        return;
    }
    size_t firstLen = arrLen / 2;
    size_t secondLen = arrLen - firstLen;
    MergeSort( arr, firstLen, comp );
    MergeSort( arr + firstLen, secondLen, comp );
    T* c = new T[arrLen];
    merge( c, arr, firstLen, arr + firstLen, secondLen, comp);
    std::memcpy( arr, c, sizeof( T ) * arrLen );
    delete[] c;
}


struct Date{
    unsigned int day;
    unsigned int month;
    unsigned int year;
    bool born_or_died; // true - дата рождения, false - дата смерти 
    bool operator<(const Date& other) const{
        if ( (year < other.year) || (year == other.year && month < other.month) || (year == other.year && month == other.month && day < other.day) ){
            return true;
        } else {
            return false;
    }
    }
    bool operator==(const Date& other) const{
        return(year == other.year && month == other.month && day == other.day);
    }
    void input(){
        std::cin >> day >> month >> year;
    }
};

struct Person {
    Date birth;
    Date death;
    bool valid;
    void input(){
        birth.input();
        birth.born_or_died = true;
        death.input();
        death.born_or_died = false;
        valid = true;
        convert();
    }
private:
    void convert(){
        // проверяем что человек дожил до 18, иначе невалиден
        Date check_age = birth;
        check_age.year += 18;
        if (death < check_age || death == check_age){
            valid = false;
            return;
        }

        // если человек страше 80, опускаем возраст до 80, возраст повышаем до 18, тк участие с 18
        check_age = birth;
        birth.year += 18;
        check_age.year += 80;
        if( check_age < death ){
            death = check_age;
            death.born_or_died = false;
        } 
    }
};

struct Group{
    int num_of_person;
    Person* group;
    int count_of_valid_dates = 0;
    Date* dates;
    explicit Group(int num): num_of_person(num), group(new Person[num_of_person]), dates(new Date[num_of_person * 2]) {}

    void input() {
        for(int i = 0; i < num_of_person; i++){
            group[i].input();
        }
        convert();
    }

    void convert(){

        for(int i = 0; i < num_of_person; i++){ // в даты добавляем только даты людей, доживших до 18
            if(group[i].valid){
                dates[count_of_valid_dates++] = group[i].birth;
                dates[count_of_valid_dates++] = group[i].death;    
            }
        }

        MergeSort<Date>(dates, count_of_valid_dates);

        for( int i = 0; i < count_of_valid_dates - 1; i++){ // если один родился, а другой умер в один день
            if (dates[i] == dates[i + 1] && (dates[i].born_or_died == true && dates[i + 1].born_or_died == false)){
                std::swap(dates[i], dates[i + 1]);
            }
        }
    }

    int max_count_of_contemporaries(){
        int counter = 0, max_counter = 0;
        for(int i = 0; i < count_of_valid_dates; i++){
            if(dates[i].born_or_died){
                counter++;
            } else{
                counter--;
            }
            if(counter > max_counter){
                max_counter = counter;
            }
        }
        return max_counter;
    }

};


int main(){
    int num_of_pers;
    std::cin >> num_of_pers;
    Group group(num_of_pers);
    group.input();
    int max_count = group.max_count_of_contemporaries();
    
    std::cout << max_count;
    return 0;
}