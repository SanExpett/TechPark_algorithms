#include <iostream>
#include <string>

using namespace std;

struct Node {
    int val;
    Node* left;
    Node* right;
    Node(int v) : val(v), left(nullptr), right(nullptr) {}
};

bool same_vals_in_nodes(Node* root, int val) {
    if (root == nullptr) {
        return true;
    }
    if (root->val != val) {
        return false;
    }
    return same_vals_in_nodes(root->left, val) && same_vals_in_nodes(root->right, val);
}

int main() {
    string line;
    getline(cin, line);
    Node* root = nullptr;
    size_t pos = 0;
    while ((pos = line.find(' ')) != string::npos) {
        int val = stoi(line.substr(0, pos));
        line.erase(0, pos + 1);
        if (root == nullptr) {
            root = new Node(val);
        } else {
            Node* cur = root;
            while (true) {
                if (val < cur->val) {
                    if (cur->left == nullptr) {
                        cur->left = new Node(val);
                        break;
                    }
                    cur = cur->left;
                } else if (val > cur->val) {
                    if (cur->right == nullptr) {
                        cur->right = new Node(val);
                        break;
                    }
                    cur = cur->right;
                } else {
                    break;
                }
            }
        }
    }
    if (!line.empty()) {
        int val = stoi(line);
        if (root == nullptr) {
            root = new Node(val);
        } else {
            Node* cur = root;
            while (true) {
                if (val < cur->val) {
                    if (cur->left == nullptr) {
                        cur->left = new Node(val);
                        break;
                    }
                    cur = cur->left;
                } else if (val > cur->val) {
                    if (cur->right == nullptr) {
                        cur->right = new Node(val);
                        break;
                    }
                    cur = cur->right;
                } else {
                    break;
                }
            }
        }
    }
    if (same_vals_in_nodes(root, root->val)) {
        cout << 1 << endl;
    } else {
        cout << 0 << endl;
    }
    return 0;
}