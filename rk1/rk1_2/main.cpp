        
#include <iostream>
#include <stack>
#include <string>

std::string stack_anagramm(std::string str_in, std::string str_out){
    std::stack<char> stack;
    int j = 0;
    for(int i = 0; i < str_in.length(); i++) {
        stack.push(str_in[i]);
        while(!stack.empty() && stack.top() == str_out[j]) {
            stack.pop();
            j++;
        }
    }
    if(stack.empty() && j == str_out.length()) {
        return "YES";
    } else {
        return "NO";
    }
}

int main() {
    std::string str_in, str_out;
    std::cin >> str_in >> str_out;

    std::cout << stack_anagramm(str_in, str_out);
    return 0;
}