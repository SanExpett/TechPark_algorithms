#include <iostream>
#include <string>
#include <unordered_set>

struct Node {
    std::string product_name;
    int color;
    int size;
};

class NodeHash {
public:
    std::size_t operator()(const Node& node) const {
        // Используем хеш-функцию для std::string и комбинируем ее с хешами для color и size
        return std::hash<std::string>()(node.product_name) ^ std::hash<int>()(node.color) ^ std::hash<int>()(node.size);
    }
};

class NodeEqual {
public:
    bool operator()(const Node& lhs, const Node& rhs) const {
        // Сравниваем все поля структуры Node
        return lhs.product_name == rhs.product_name && lhs.color == rhs.color && lhs.size == rhs.size;
    }
};

int main() {
    std::unordered_set<Node, NodeHash, NodeEqual> nodes;

    char op;
    std::string product_name;
    int color, size;

    while (std::cin >> op >> product_name >> color >> size) {
        Node node{product_name, color, size};
        if (op == '+') {
            auto [it, inserted] = nodes.insert(node);
            std::cout << (inserted ? "OK" : "FAIL") << std::endl;
        } else if (op == '-') {
            std::size_t erased = nodes.erase(node);
            std::cout << (erased ? "OK" : "FAIL") << std::endl;
        } else if (op == '?') {
            auto it = nodes.find(node);
            std::cout << (it != nodes.end() ? "OK" : "FAIL") << std::endl;
        }
    }

    return 0;
}