#include <iostream>
#include <queue>
#include <stack>

using namespace std;

struct Node {
    int value = 0;
    Node* left = nullptr;
    Node* right = nullptr;

    Node() {}
    Node(int val) : value(val) {}
};

class BinaryTree {
private:
    Node* root = nullptr;

private:
    int _maxHeight(Node* n) {
        if (n == nullptr) {
            return 0;
        }
        return 1 + max(_maxHeight(n->left), _maxHeight(n->right));
    }
public:

    int maxHeight() {
        return _maxHeight(root);
    }

    void insert(int val) {
        if (root == nullptr) {
            root = new Node(val);
            return;
        }
        queue<Node*> q;
        q.push(root);
        while (!q.empty()) {
            Node* curr = q.front(); q.pop();
            if (curr->left == nullptr) {
                curr->left = new Node(val);
                return;
            }
            if (curr->right == nullptr) {
                curr->right = new Node(val);
                return;
            }
            q.push(curr->left);
            q.push(curr->right);
        }
    }

    void printPostOrder() {
        if (root == nullptr) {
            return;
        }
        Node* iter = root;
        stack<Node*> st;
        while (iter != nullptr || !st.empty()) {
            while (iter != nullptr) {
                st.push(iter);
                iter = iter->right;
            }
            Node* curr = st.top(); st.pop();
            cout << curr->value << " ";

            iter = curr->left;
        }
        cout << endl;
    }

    void printInOrder() {
        if (root == nullptr) {
            return;
        }
        Node* iter = root;
        stack<Node*> st;
        while (iter != nullptr || !st.empty()) {
            while (iter != nullptr) {
                st.push(iter);
                iter = iter->left;
            }
            Node* curr = st.top(); st.pop();
            cout << curr->value << " ";

            iter = curr->right;
        }
        cout << endl;
    }

    void printBF() {
        if (root == nullptr) {
            return;
        }
        queue<Node*> q;
        q.push(root);
        while (!q.empty()) {
            int levelSize = q.size();
            while (levelSize--) {
                Node* curr = q.front(); q.pop();
                cout << curr->value << " ";
                if (curr->left != nullptr) {
                    q.push(curr->left);
                }
                if (curr->right != nullptr) {
                    q.push(curr->right);
                }
            }
        }
        cout << endl;
    }
};

int main() {
    BinaryTree tree;
    for (int i = 1; i <= 9; i++) {
        tree.insert(i);
    }
    tree.printPostOrder();
    tree.printInOrder();
    tree.printBF();
    cout << tree.maxHeight() << endl;

    return 0;
}