#include <iostream>
#include <algorithm>
#include <queue>
#include <sstream>

struct Node {
    int value;
    Node* left;
    Node* right;

    Node(int value) : value(value), left(nullptr), right(nullptr) {}
};

int shortest_path(Node* root) {
    if (root == nullptr) {
        return 0;
    }
    if (root->left == nullptr || root->right == nullptr) {
        return 1;
    }
    if (root->left == nullptr) {
        return 1 + shortest_path(root->right);
    }
    if (root->right == nullptr) {
        return 1 + shortest_path(root->left);
    }
    return 1 + std::min(shortest_path(root->left), shortest_path(root->right));
}

int main() {
    // Создаем корень дерева
    Node* root = nullptr;

    // Очередь для хранения узлов, которые нужно обработать
    std::queue<Node*> q;

    // Считываем строку из ввода
    std::string line;
    std::getline(std::cin, line);

    // Создаем поток для чтения значений из строки
    std::istringstream iss(line);

    // Считываем значения узлов из потока
    int value;
    while (iss >> value) {
        // Создаем новый узел
        Node* node = new Node(value);

        // Если корень еще не был создан, то создаем его
        if (root == nullptr) {
            root = node;
        }
        // Иначе добавляем узел в очередь для обработки
        else {
            Node* parent = q.front();
            if (parent->left == nullptr) {
                parent->left = node;
            }
            else {
                parent->right = node;
                q.pop();
            }
        }

        // Добавляем узел в очередь для обработки
        q.push(node);
    }

    // Вычисляем кратчайший путь от корня до листа
    std::cout << shortest_path(root) << std::endl;

    return 0;
}