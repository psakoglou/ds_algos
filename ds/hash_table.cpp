#include <iostream>
#include <vector>
#include <list>

// open addressing
class HT {
private:
    enum Status {OCCUPIED, EMPTY, DELETED};

    struct Node {
        std::string key;
        int value = -1;
        Status status = EMPTY;
    };
private:
    int hash(std::string key) {
        return std::hash<std::string>()(key);
    }
    void _insert(Node n) {
        int idx = hash(n.key) % size;

        int i = idx;
        while (table[i].status == OCCUPIED) {
            if (table[i].key == n.key) {
                return;
            }
            i = (i + 1) % size;
            if (i == idx) return;
        }
        n.status = OCCUPIED;
        table[i] = n;
    }
    void resize() {
        Node* oldTable = table;
        std::size_t oldSize = size;

        size *= resizeScalar;
        table = new Node[size];
        for (int i = 0; i < size; i++) {
            table[i].status = EMPTY;
        }

        for (int i = 0; i < oldSize; i++) {
            if (oldTable[i].status == OCCUPIED) {
                _insert(oldTable[i]);
            }
        }

        delete[] oldTable;
    }
private:
    Node* table = nullptr;
    std::size_t size = 100;
    std::size_t elemsN = 0;
    const double resizeScalar = 2;
    const double loadFactor = 1;
public:

    HT() {
        table = new Node[size];
    }

    ~HT() {
        if (table != nullptr) {
            delete[] table;
        }
    }

    void insert(Node n) {
        if ((double)elemsN / (double)size > loadFactor) {
            resize();
        }

        int idx = hash(n.key) % size;

        int i = idx;
        while (table[i].status == OCCUPIED) {
            if (table[i].key == n.key) {
                return;
            }
            i = (i+1) % size;
            if (i == idx) return;
        }
        n.status = OCCUPIED;
        table[i] = n;
        elemsN++;
    }


    
};

// chaining
class HashTable {
private:
    struct Node {
        std::string key;
        int value;

        int hash() {
            return std::hash<std::string>()(key);
        }
    };
private:
    std::vector<std::list<Node>> table; 
    std::size_t capacity = 100;
public:

    HashTable() = default;

    // insert
    void insert(Node n) {
        int idx = n.hash() % capacity;
        table[idx].push_back(n);
    }

    // delete

    // get
    Node* get(std::string key) {
        int idx = std::hash<std::string>()(key);
        if (table[idx].empty()) {
            return nullptr; 
        }
        auto iter = table[idx].begin();
        auto end = table[idx].end();
        while (iter != end) {
            if (iter->key == key) {
                return &(*iter); 
            }
            iter++;
        }
        return nullptr;
    }

    // visualize


};


int main() {

    return 0;
}