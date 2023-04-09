// Реализовать очередь с помощью двух стеков.
// Требования: Очередь должна быть реализована в виде класса. Стек тоже должен быть реализован в виде класса.

#include <iostream>
#include "assert.h"
#include <sstream>
using namespace std;

// Стек целых чисел, реализованный с помощью массива.
template<typename T>
class Stack {
public:
    explicit Stack( int _bufferSize ) : bufferSize( _bufferSize ),top(-1 ){
        buffer = new T[bufferSize]; // Создаем буфер.
    }
    ~Stack(){
        delete[] buffer; // Удаляем буфер.
    }
    // Добавление и извлечение элемента из стека.
    void push( const T& value ) {
        // assert( top + 1 < bufferSize );
        if( top + 1 == bufferSize) 
            grow();
        assert( top + 1 < bufferSize && buffer != 0 );
        buffer[++top] = value;
    }
    T pop() {
        assert( top != -1 );
        return buffer[top--];
    }
    // Проверка на пустоту.
    bool is_empty() const { return top == -1; }
private:
    void grow() {
        int newBufferSize = bufferSize * 2;
        T* newBuffer = new T[newBufferSize];

        for( int i = 0; i < top+1; ++i) 
            newBuffer[i] = buffer[i];
        delete[] buffer;
        buffer = newBuffer;
        bufferSize = newBufferSize;
    }
    T* buffer;
    int bufferSize;
    int top; // Индекс верхнего элемента.
    
};



template<typename T>
class Queue{
public:
    Queue() : stack_in(10), stack_out(10) {}

    ~Queue(){
        while(!is_empty()){
            pop();
        }
     }

    Queue(const Queue&) = delete;
    Queue& operator=(const Queue&) = delete;

    bool is_empty() const{return (stack_in.is_empty() && stack_out.is_empty());}

    void push(const T& value){
        stack_in.push(value);
    }
    T pop(){
        if(stack_out.is_empty()){
            while(!stack_in.is_empty()){
                stack_out.push(stack_in.pop());
            }
        }
        return stack_out.pop();
    }

private:
    Stack<T> stack_in;
    Stack<T> stack_out;

};


void test_queue(){
    {
        Queue<int> q;
        assert(q.is_empty());
    }

    {
        Queue<int> q;
        q.push(1);
        assert(!q.is_empty());

        int v = q.pop();
        assert(v == 1);

        assert(q.is_empty());
    }

    {
        Queue<int> q;

        for(int i = 0; i < 100; i++){
            q.push(i);
        }
        
        for(int i = 0; i < 100; i++){
            assert(q.pop() == i);
        }

        assert(q.is_empty());
    }

    {
        Queue<string> q;
        q.push("1");
        q.push("2");
        assert(!q.is_empty());

        assert(q.pop() == "1");
        assert(q.pop() == "2");
        assert(q.is_empty());
    }
    
    cout << "tests queue OK" << endl;
}



int run(istream& input, ostream& output){
   Queue<int> q;
    int commands_count = 0;
    input >> commands_count;
    
    for(int i = 0; i < commands_count; i++){
        int command = 0;
        int expected = 0;
        input >> command >> expected;
        switch(command){
            case 2: //pop
                {
                    int value = q.is_empty() ? -1 : q.pop();
                    if(value != expected){
                        output << "NO" << endl;
                        return 0;
                    }
                    
                }
                break;
            case 3:
                q.push(expected);
                break;
            default:
                output << "NO" << endl;
                return 0;
        }
    }
    output << "YES" << endl;
    return 0;
}

void test_logic(){
    {
        stringstream input;
        stringstream output;
        input << "3" << endl;
        input << "3 44" << endl;
        input << "3 50" << endl;
        input << "2 44" << endl;
        run(input, output);

        assert(output.str() == "YES\n");
    }

    {
        stringstream input;
        stringstream output;
        input << "2" << endl;
        input << "2 -1" << endl;
        input << "3 10" << endl;
        run(input, output);

        assert(output.str() == "YES\n");
    }

    {
        stringstream input;
        stringstream output;
        input << "2" << endl;
        input << "3 44" << endl;
        input << "2 66" << endl;
        run(input, output);

        assert(output.str() == "NO\n");
    }
    cout << "tests logic OK" << endl;
}

void run_tests(){
    test_queue();
    test_logic();
}

int main(){
    // run_tests();
    return run(cin, cout);
}