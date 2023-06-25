#include <iostream>
#include <stack>

template <typename T>
struct DefaultComparator {
    bool operator() (const T& l, const T& r) const {
        return l < r;
    }
};

template< typename T, typename Comparator = DefaultComparator<T> >
class BinaryTree {
 private:

  class Node {
   public:
    T value;
    Node* left;
    Node* right;
    Node(const T& val) : value(val), left(nullptr), right(nullptr) {}
  };

  Comparator comp;
  Node* root;
  size_t count_of_elements;

 public:
  BinaryTree(Comparator comp = Comparator()) : root(nullptr), count_of_elements(0) {}

  ~BinaryTree() {
      if (!root) return;
      std::stack<Node*> st;
      st.push(root);
      while (!st.empty()) {
        auto node = st.top();
        st.pop(); 
        if (node->left) st.push(node->left);  
        if (node->right) st.push(node->right);
        delete node;
      }
      root = nullptr; 
  };

  void add_element(const T& val) {
    count_of_elements++;
    Node* node = new Node(val);
    if (!root) {
      root = node;
      return;
    }

    Node* cur = root;

    for (size_t i = 0; i <= count_of_elements; i++) {
      if (comp(val, cur->value)) {
        if (!cur->left) {
          cur->left = node;
          return;
        } else {
          cur = cur->left;
        }
      } else {
        if (!cur->right) {
          cur->right = node;
          return;
        } else {
          cur = cur->right;
        }
      }
    }
  }

  template<typename Function>
  void post_order(Function func) {
    if (root == nullptr) return;
    std::stack<Node*> s1, s2;
    s1.push(root);
    while (!s1.empty()) {
      auto current_node = s1.top();
      s1.pop();
      s2.push(current_node);
      if (current_node->left != nullptr) {
        s1.push(current_node->left);
      }
      if (current_node->right != nullptr) {
        s1.push(current_node->right);
      }
    }
    while (!s2.empty()) {
      auto current_node = s2.top();
      func(current_node);
      s2.pop();
    }
  }
};

int main() {
  BinaryTree<int> bt;
  int n;
  std::cin >> n;
  for (int i = 0; i < n; i++) {
    int el;
    std::cin >> el;
    bt.add_element(el);
  }
  bt.post_order([](const auto& node) { std::cout << node->value << " "; });
  return 0;
}

