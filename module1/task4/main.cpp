#include <iostream>

struct User {
    int id;
    int visits;
    bool operator<(const User& other) const {
        return this->visits < other.visits;
    }
    bool operator>(const User& other) const {
        return this->visits > other.visits;
    }
};

template <typename T>
struct DefaultComparator {
    bool operator() (const T& l, const T& r) const {
        return l > r;
    }
};

template < typename T, typename Comparator = DefaultComparator<T> >
void sort( T* arr, size_t size, Comparator comp = Comparator() ){
    size_t l = 0;
    size_t r = size;
    for(size_t i = l; i < r; i++){
        for(size_t j = l; j < r - 1; j++){
            if( comp(arr[j + 1], arr[j]) ){
                swap(arr[j + 1], arr[j]);
            }
        }
    }
}

//КУЧА
template<typename T, typename Comparator = DefaultComparator<T>>
class Heap {
private:
    T* elements;
    size_t size_;
    size_t buffer_;
    Comparator comp;
public:
    Heap(size_t buffer=10, Comparator c=Comparator()):
        elements(new T[buffer]), size_(0), buffer_(buffer), comp(c)
    {
    }
    ~Heap() {
        delete[] elements;
    } 
    bool empty() const {
        return size_ == 0;
    }
    size_t size() const {
        return size_;
    }

    void push(const T &element) {
        if(size_ == buffer_)
            resize();
        elements[size_] = element;
        sift_up(size_++);
    }

    void pop() {
        if (!empty()) {
            std::swap(elements[0], elements[size_-1]);
            size_--;
            sift_down(0);
        }
    }

    const T &top() const {
        return elements[0];
    }

private:
    void sift_up(size_t index) {
        while (index > 0) {
            size_t parent_index = (index - 1) / 2;
            if (comp(elements[parent_index], elements[index])) {
                std::swap(elements[parent_index], elements[index]);
                index = parent_index;
            } else {
                break;
            }
        }
    }

    void sift_down(size_t index) {
        size_t left_child_index = index * 2 + 1;
        size_t right_child_index = index * 2 + 2;
        size_t largest_index = index;
        if (left_child_index < size_ && comp(elements[largest_index], elements[left_child_index])) {
            largest_index = left_child_index;
        }
        if (right_child_index < size_ && comp(elements[largest_index], elements[right_child_index])) {
            largest_index = right_child_index;
        }
        if (largest_index != index) {
            std::swap(elements[largest_index], elements[index]);
            sift_down(largest_index);
        }
    }
    void resize() {
        T* new_elements = new T[buffer_ * 2];
        std::copy(elements, elements + size_, new_elements);
        delete[] elements;
        elements = new_elements;
        buffer_ *= 2;
    }
};

void find_topK_users(User* data, int n, int k, User* res) {
    Heap<User, DefaultComparator<User>> heap(k, DefaultComparator<User>());
    for (int i = 0; i < n; i++) {
        if (heap.size() < k) {
            heap.push(data[i]);
        } else if (data[i].visits > heap.top().visits) {
            heap.pop();
            heap.push(data[i]);
        }
    }
    for (int i = k-1; i >= 0; i--) {
        res[i] = heap.top();
        heap.pop();
    }
}


int main() {
    int n, k;
    std::cin >> n >> k;
    User data[n];
    for (int i = 0; i < n; i++) {
        std::cin >> data[i].id >> data[i].visits;
    }
    User topK[k];
    find_topK_users(data, n, k, topK);
    for (int i = k - 1; i >= 0; i--) {
        std::cout << topK[i].id << " ";
    }
    return 0;
}