// flatten two trees and merge them into a list
// flatten one tree into a list
#include <iostream>

class BTree {
    struct Node {
        int value;
        Node* left = nullptr;
        Node* right = nullptr;
        Node(int val) : value(val) {}
    };

    Node* root = nullptr;
    int elemsN = 0;

    void del_(Node* r) {
        if (r == nullptr) {
            return;
        }
        del_(r->left);
        del_(r->right);
        delete r;
    }

    void insert_(Node*& r, int val) {
        if (r == nullptr) {
            r = new Node(val);
            return;
        }
        if (r->value <= val) {
            insert_(r->right, val);
        } else {
            insert_(r->left, val);
        }
    }

    void printTree_(Node* n) {
        if (n == nullptr) {
            return;
        }
        std::cout << n->value << " ";
        printTree_(n->left);
        printTree_(n->right);
    }

    Node* find_(Node* root, int val) {
        if (root == nullptr) {
            return nullptr;
        }
        if (root->value == val) {
            return root;
        }
        if (root->value < val) {
            return find_(root->right, val);
        } else {
            return find_(root->left, val);
        }
    }

    void delete_(Node* root, int val) {
        if (root == nullptr) {
            return;
        }
        if (root->value == val) {

        }
        if (root->value < val) {
            delete_(root->right, val);
        } else {
            delete_(root->left, val);
        }

    }

    void printInOrder_(Node* n) {
        if (n == nullptr) {
            return;
        }
        printInOrder_(n->left);
        std::cout << n->value << " ";
        printInOrder_(n->right);
    }

    void printBackwards_(Node* n) {
        if (n == nullptr) {
            return;
        }
        printBackwards_(n->right);
        std::cout << n->value << " ";
        printBackwards_(n->left);
    }

    Node* treemaxrec_(Node* iter) {
        if (iter == nullptr) {
            return nullptr;
        }
        if (iter->right != nullptr) {
            return treemaxrec_(iter->right);
        } else {
            return iter;
        }
    }

    Node* treeminrec_(Node* iter) {
        if (iter == nullptr) {
            return nullptr;
        }
        if (iter->left != nullptr) {
            return treeminrec_(iter->left);
        } else {
            return iter;
        }
    }

    public:

    BTree() = default;

    ~BTree() {
        if (root == nullptr) {
            return;
        }
        del_(root);
    }

    void insert(int val) {
        insert_(root, val);
    }

    void del(int val) {
        return delete_(root, val);
    }

    void print() {
        printTree_(root);
        std::cout << std::endl;
    }

    void printBackwards() {
        printBackwards_(root);
        std::cout << std::endl;
    }

    void printInOrder() {
        printInOrder_(root);
        std::cout << std::endl;
    }

    Node* find(int val) {
        return find_(root, val);
    }

    Node* treemax() {
        if (root == nullptr) {
            return root;
        }
        Node* iter = root;
        while (iter->right != nullptr) {
            iter = iter->right;
        }
        return iter;
    }

    Node* treemaxrec() {
        return treemaxrec_(root);
    }

    Node* treeminrec() {
        return treeminrec_(root);
    }

    Node* treemin() {
        if (root == nullptr) {
            return root;
        }
        Node* iter = root;
        while (iter->left != nullptr) {
            iter = iter->left;
        }
        return iter;
    }
};

int main() {

    try {
        BTree tree;
        tree.insert(10);
        tree.insert(5);
        tree.insert(12);
        tree.insert(6);
        tree.insert(12);
        tree.insert(4);
        tree.insert(4);
        tree.insert(13);
        tree.insert(11);
        tree.insert(18);
        tree.insert(19);
        tree.insert(1);
        tree.insert(2);
        tree.insert(9);
        tree.insert(8);
        tree.insert(7);

        tree.print();
        tree.printInOrder();
        tree.printBackwards();

        std::cout << "found: " << tree.find(10)->value << std::endl;
        std::cout << "found: " << tree.find(1)->value << std::endl;
        std::cout << "found: " << tree.find(4)->value << std::endl;
        std::cout << "found: " << tree.find(19)->value << std::endl;
        std::cout << "found: " << tree.find(18)->value << std::endl;
        std::cout << "not found: " << (tree.find(100) == nullptr ? "correct" : "incorrect") << std::endl;
        std::cout << "not found: " << (tree.find(-100) == nullptr ? "correct" : "incorrect") << std::endl;
        std::cout << "not found: " << (tree.find(0) == nullptr ? "correct" : "incorrect") << std::endl;
        std::cout << "not found: " << (tree.find(16) == nullptr ? "correct" : "incorrect") << std::endl;

        std::cout << "max: " << tree.treemax()->value << std::endl;
        std::cout << "min: " << tree.treemin()->value << std::endl;
        std::cout << "max rec: " << tree.treemaxrec()->value << std::endl;
        std::cout << "min rec: " << tree.treeminrec()->value << std::endl;
    } catch (std::exception& e) {
        std::cout << e.what() << std::endl;
    }
    
    return 0;
}