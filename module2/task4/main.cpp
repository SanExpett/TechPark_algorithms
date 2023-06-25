#include <iostream>
#include <stack>
#include <vector>

template<typename T>
struct DefaultComparator {
    int operator()(const T& l, const T& r) {
        if (l < r) return -1;
        if (l > r) return 1;
        return 0;
    }
};


template<typename T, typename Comparator=DefaultComparator<T> >
class AVLTree {
public:
    struct Node {
        T key; 
        uint8_t height; 
        int count_of_nodes; 
        
        
        Node* left;
        Node* right;

        Node(int k) : key(k), height(1), count_of_nodes(1), left(nullptr) , right(nullptr) {}
    };

    AVLTree(Comparator comp = Comparator()): root(nullptr), comp(comp) {}
    ~AVLTree() {
        postorder_delete(root);
    }

    void postorder_delete(Node* root) {
        if (!root) {
            return;
        }

        std::stack<Node*> stack;
        stack.push(root);

        while (!stack.empty()) {
            Node* node = stack.top();
            stack.pop();

            if (node->left) {
                stack.push(node->left);
            }

            if (node->right) {
                stack.push(node->right);
            }

            delete node;
        }
    }

    void insert(T k, int& position) {
        root = insert_aux(k, position, root);
    }

    void erase(int pos) {
        root = erase_aux(pos, root);
    }

private:
    
    Node* insert_aux(T k, int& position, Node* node ) {
        if( !node ) {
            return new Node(k);
        }
        ++(node->count_of_nodes);
        int cmp_res = comp(k, node->key);
        if( cmp_res == -1 ) {
            position += count_of_nodes(node->right) + 1;
            node->left = insert_aux(k, position, node->left);
        } else
            node->right = insert_aux(k, position, node->right);

        return balance(node);
    }

    Node* erase_aux(int pos, Node* node ) {
        if( !node ) {
            return nullptr;
        }
        if( pos >= node->count_of_nodes ) {
            return node;
        }
        
        int current = 0;
        std::stack<Node*> nodes_st;

        while( true ) {
            int count_of_nodes_right = count_of_nodes(node->right);
            if( pos - current > count_of_nodes_right ) {
                nodes_st.push(node);
                node = node->left;
                current += count_of_nodes_right + 1;
            } 
            else if( pos - current < count_of_nodes_right ) {
                if( node->right != nullptr ) {
                    nodes_st.push(node);
                    node = node->right;
                } else {
                    break;
                }
            } else {
                Node *left = node->left;
                Node *right = node->right;
                T key = node->key;

                delete node;

                if( !right ) {
                    if( !left ) {
                        if( !nodes_st.empty() ) {
                            node = nodes_st.top();
                            nodes_st.pop();
                            if (node->key > key) {
                                node->left = nullptr;
                            } else {
                                node->right = nullptr;
                            }

                            --node->count_of_nodes;
                        } else {
                            return nullptr;
                        }
                    } else {
                        node = left;
                    }
                } else {
                    Node* min = find_min(right);
                    min->right = erase_min(right);
                    min->left = left;
                    fix_count_of_nodes(min);
                    node = balance(min);
                }
                break;
            }
        }

        return fix_nodes_stack(nodes_st, node);
    }


    Node* fix_nodes_stack(std::stack<Node*>& nodes_st, Node* node) { // для erase_aux
        while( !nodes_st.empty() ) {
            Node *temp_node = nodes_st.top();
            --temp_node->count_of_nodes;

            if( comp(temp_node->key, node->key) == 1 ) {
                temp_node->left = node;
            } else {
                temp_node->right = node;
            }

            node = balance(temp_node);
            nodes_st.pop();
        }

        return node;
    }   


    uint8_t height(Node* node) {
        if (node) {
            return node->height;
        } else {
            return 0;
        }
    }



    int bfactor(Node* node) {
        return height(node->right) - height(node->left);
    }


    int count_of_nodes(Node* node) {
        if (node) {
            return node->count_of_nodes; 
        } else {
            return 0;
        }
    }


    void fix_count_of_nodes(Node* node) {
        int left_count_of_nodes = count_of_nodes(node->left);
        int right_count_of_nodes = count_of_nodes(node->right);

        node->count_of_nodes = left_count_of_nodes + right_count_of_nodes + 1;
    }


    void fix_height(Node* node) {
        uint8_t left_height = height(node->left);
        uint8_t right_height = height(node->right);
        

        node->height = std::max(right_height, left_height) + 1;
    }

    Node* rotate_right(Node* node) {
        Node* temp_node = node->left;
        node->left = temp_node->right;
        temp_node->right = node;

        fix_count_of_nodes(node);
        fix_count_of_nodes(temp_node);
        fix_height(temp_node);
        fix_height(node);

        return temp_node;
    }

    Node* rotate_left(Node* node) {
        Node* temp_node = node->right;
        node->right = temp_node->left;
        temp_node->left = node;

        fix_count_of_nodes(node);
        fix_count_of_nodes(temp_node);
        fix_height(node);
        fix_height(temp_node);

        return temp_node;
    }

    Node* balance(Node* node) {
        fix_height(node);
        if( bfactor(node) == 2 ) {
            if( bfactor(node->right) < 0 )
                node->right = rotate_right(node->right);
            return rotate_left(node);
        }
        if( bfactor(node) == -2 ) {
            if( bfactor(node->left) > 0 )
                node->left = rotate_left(node->left);
            return rotate_right(node);
        }

        return node;
    }

    Node* find_min(Node* node) {
        if ( node->left ) {
            return find_min(node->left);
        } else {
            return node;
        }
    }


    Node* erase_min(Node* node) {
        if( node->left == 0 )
            return node->right;

        node->left = erase_min(node->left);
        --node->count_of_nodes;

        return balance(node);
    }

    Node* root;
    Comparator comp;

};

int main()
{
    int n;
    std::cin >> n;
    AVLTree<int, DefaultComparator<int>> tree;
    std::vector<int> results;

    int command, key, pos;

    for( size_t i = 0; i < n; ++i ) {
        std::cin >> command;
        if( command == 1 ){
            pos = 0;
            std::cin >> key;
            tree.insert(key, pos);
            results.push_back(pos);
        } else if ( command == 2 ) {
            std::cin >> key;
            tree.erase(key);
        }
    }

    for (auto el: results) {
        std::cout << el << std::endl;
    }

    return 0;
}