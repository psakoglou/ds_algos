#include <iostream>
#include <functional>

struct Node {
    Node(int inp) {
        data = inp;
        next = nullptr;
    }
    int data;
    Node* next;
};

class LinkedList {
    private:

    Node* m_head = nullptr;
    Node* m_tail = nullptr;
    std::size_t m_count = 0;

    public:

    LinkedList() = default;

    ~LinkedList() {
        while (m_head != nullptr) {
            Node* next = m_head->next;
            delete m_head;
            m_head = next;
        }
    }

    // init
    void init(std::initializer_list<int>& inp) {
        try {
            std::size_t n = inp.size();
            std::size_t idx = 0;
            while (idx < n) {
                push_back(*(inp.begin() + idx));
                idx++;
            }

        } catch (const std::exception& e) {
            std::cout << e.what() << std::endl;
        }
    }

    // size
    std::size_t size() {
        return m_count;
    }
    // insert
    void insert(int data, int pos) {
        if (pos >= m_count + 1 || pos < 0) {
            return;
        }
        if (pos == 0) { 
            push_front(data); // O(1)
        }
        if (pos == m_count) {
            push_back(data); // O(1)
        }
        // O(n)
        // find location to insert
        Node* temp = m_head;
        std::size_t i = 0;
        while (temp != nullptr && i < pos) {
            temp = temp->next;
            i++;
        }
        if (temp == nullptr) {
            return;
        }
        // insert
        Node* newNode = new Node(data);
        newNode->next = temp->next;
        temp->next = newNode;
        m_count++;
    }

    // delete
    void removeAt(std::size_t pos) {
        if (pos == 0) {
            popHead();
        }
        if (pos == m_count) {
            popTail();
        }
        Node* prevNode = getNodeAtPos(pos - 1); 
        if (prevNode != nullptr && prevNode->next != nullptr) {
            Node* newNext = prevNode->next->next;
            delete prevNode->next;
            prevNode->next = newNext;
            m_count--;
        }
    }

    void popHead() {
        if (m_head != nullptr) {
            Node* newHead = m_head->next;
            delete m_head;
            m_head = newHead;
            m_count--;
        }
    }
    void popTail() {
        if (m_head != nullptr) {
            Node* iter = m_head;
            Node* prev = iter;
            while (iter->next != nullptr) {
                prev = iter;
                iter = iter->next;
            }
            delete iter;
            m_tail = prev;
            m_count--;
        }
    }

    void remove(int data) {
        if (m_head == nullptr) {
            return;
        }
        Node* iter = m_head;
        Node* prev = m_head;
        while (iter->next != nullptr && iter->data != data) {
            prev = iter;
            iter = iter->next;
        }
        Node* newNext = iter->next;
        delete iter;
        prev->next = newNext;
        m_count--;
        if (m_tail == nullptr) {
            m_tail = newNext;
        }
    }

    Node* find(int data) {
        Node* temp = m_head;
        while (temp != nullptr) {
            if (temp->data == data) {
                return temp;
            }
            temp = temp->next;
        }
        return nullptr;
    }

    Node* getNodeAtPos(std::size_t pos) {
        if (pos < 0 || pos > m_count + 1) {
            return nullptr;
        }
        Node* iter = m_head;
        std::size_t i = 0;
        while (iter != nullptr && i < pos) {
            iter = iter->next;
            i++;
        }
        return iter;
    }

    // push front
    void push_front(int data) {
        if (m_head == nullptr) {
            m_head = new Node(data);
            m_tail = m_head;
            m_count++;
            return;
        }
        Node* newHead = new Node(data);
        newHead->next = m_head;
        m_head = newHead;
        m_count++;
    }

    // push back
    void push_back(int data) {
        if (m_head == nullptr) {
            m_head = new Node(data);
            m_tail = m_head;
            m_count++;
            return;
        }
        Node* newTail = new Node(data);
        m_tail->next = newTail;
        m_tail = newTail;
        m_count++;
    }

    // reverse
    void reverse() {

    }

    // traverse
    void traverse() {
        Node* iter = m_head;
        while (iter != nullptr) {
            std::cout << "[ " << iter->data << " ] " << (iter->next != nullptr) ? "" : "\n";
            iter = iter->next;
        }
    }

    // copy
    Node* copy() {
        if (m_head == nullptr) {
            return nullptr;
        }

        Node* newListHead = new Node(m_head->data);
        Node* newListIter = newListHead;
        Node* currListIter = m_head->next;
        while (currListIter != nullptr) {
            Node* newNode = new Node(currListIter->data);
            newListIter->next = newNode;
            newListIter = newListIter->next;
            currListIter = currListIter->next;
        }
        return newListHead;
    }

    // apply (a function on each element)
    void apply(std::function<void(int)> f) {
        Node* iter = m_head;
        while (iter != nullptr) {
            f(iter->data);
            iter = iter->next;
        }
    }

};

bool check(bool condition, const std::string& testName) {
    if (condition) {
        std::cout << "[PASS] " << testName << "\n";
        return true;
    } else {
        std::cout << "[FAIL] " << testName << "\n";
        return false;
    }
}


int main() {
    LinkedList list;

    // --- TEST 1: push_front ---
    list.push_front(10);
    list.push_front(20);
    list.push_front(30);
    check(list.size() == 3, "push_front adds elements (size == 3)");

    // --- TEST 2: push_back ---
    list.push_back(40);
    list.push_back(50);
    check(list.size() == 5, "push_back adds elements (size == 5)");

    // --- TEST 3: insert at position ---
    list.insert(15, 1);   // valid insert
    list.insert(60, list.size()); // append at end
    list.insert(70, -1);  // invalid insert, ignored
    check(list.find(15) != nullptr, "insert at pos 1 works");
    check(list.find(60) != nullptr, "insert at tail works");
    check(list.find(70) == nullptr, "insert at invalid pos ignored");

    // --- TEST 4: remove by value ---
    list.remove(20);   // should remove
    list.remove(999);  // non-existent, should ignore
    check(list.find(20) == nullptr, "remove by value works");
    check(list.size() == 6, "remove by value updates size");

    // --- TEST 5: remove head ---
    size_t oldSize = list.size();
    list.removeAt(0);
    check(list.size() == oldSize - 1, "removeAt(0) reduces size");

    // --- TEST 6: remove tail ---
    oldSize = list.size();
    list.removeAt(list.size() - 1);
    check(list.size() == oldSize - 1, "remove tail reduces size");

    // --- TEST 7: remove middle ---
    oldSize = list.size();
    if (oldSize >= 2) list.removeAt(1);
    check(list.size() == oldSize - 1, "remove middle node reduces size");

    // --- TEST 8: find elements ---
    check(list.find(50) != nullptr, "find existing element works");
    check(list.find(999) == nullptr, "find non-existing returns null");

    // --- TEST 9: copy list ---
    Node* copyHead = list.copy();
    int copyCount = 0;
    for (Node* iter = copyHead; iter; iter = iter->next) copyCount++;
    check(copyCount == list.size(), "copy creates same number of nodes");
    // check deep copy (not same pointer)
    check(copyHead != nullptr && copyHead != list.find(copyHead->data), "copy is deep (head differs)");

    // --- TEST 10: apply function ---
    int sum = 0;
    list.apply([&sum](int val) { sum += val; });
    check(sum > 0, "apply function iterates through elements");

    // --- TEST 11: initializer_list init ---
    LinkedList list2;
    std::initializer_list<int> initList = {1, 2, 3, 4};
    list2.init(initList);
    check(list2.size() == 4, "init with initializer_list works");
    check(list2.find(3) != nullptr, "initializer_list elements inserted correctly");

    // --- TEST 12: removing all nodes one by one ---
    while (list2.size() > 0) {
        list2.removeAt(0);
    }
    check(list2.size() == 0, "removing all nodes empties list");

    // --- TEST 13: push after full deletion ---
    list2.push_back(100);
    list2.push_front(50);
    check(list2.size() == 2 && list2.find(50) && list2.find(100),
          "push works after list was cleared");

    // --- TEST 14: stress test (many inserts) ---
    LinkedList bigList;
    const int N = 1000;
    for (int i = 0; i < N; i++) bigList.push_back(i);
    check(bigList.size() == N, "stress test insertion of 1000 elements");
    bigList.removeAt(0);
    bigList.removeAt(bigList.size() - 1);
    check(bigList.size() == N - 2, "stress test removals head & tail");

    // --- TEST 15: apply modifies values (simulate doubling) ---
    int doubleSum = 0;
    bigList.apply([&doubleSum](int val) { doubleSum += val * 2; });
    check(doubleSum > 0, "apply modifies and accumulates correctly");

    // --- TEST 16: edge cases on empty list ---
    LinkedList emptyList;
    emptyList.removeAt(0);   // should do nothing
    emptyList.remove(10);    // should do nothing
    check(emptyList.size() == 0, "edge case remove on empty list safe");
    check(emptyList.find(1) == nullptr, "edge case find in empty returns null");

        // --- TEST 17: reverse empty list ---
    LinkedList revList1;
    revList1.reverse(); // should not crash or change size
    check(revList1.size() == 0, "reverse on empty list safe");

    // --- TEST 18: reverse single-element list ---
    LinkedList revList2;
    revList2.push_back(42);
    revList2.reverse();
    check(revList2.size() == 1 && revList2.find(42) != nullptr,
          "reverse on single-element list keeps same element");

    // --- TEST 19: reverse two-element list ---
    LinkedList revList3;
    revList3.push_back(1);
    revList3.push_back(2);
    revList3.reverse();
    // after reverse, head should now be 2
    check(revList3.getNodeAtPos(0)->data == 2 &&
          revList3.getNodeAtPos(1)->data == 1,
          "reverse two-element list swaps order");

    // --- TEST 20: reverse multiple-element list ---
    LinkedList revList4;
    for (int i = 1; i <= 5; ++i) revList4.push_back(i); // 1->2->3->4->5
    revList4.reverse();
    // after reverse, head should now be 5
    check(revList4.getNodeAtPos(0)->data == 5 &&
          revList4.getNodeAtPos(4)->data == 1,
          "reverse five-element list flips order");

    // --- TEST 21: reverse twice returns to original ---
    revList4.reverse(); // back to original order
    check(revList4.getNodeAtPos(0)->data == 1 &&
          revList4.getNodeAtPos(4)->data == 5,
          "double reverse restores original order");

    // --- TEST 22: reverse after removals ---
    LinkedList revList5;
    for (int i = 0; i < 6; ++i) revList5.push_back(i);
    revList5.removeAt(0);    // remove head
    revList5.removeAt(revList5.size() - 1); // remove tail
    revList5.reverse();
    // check size unchanged and first element is formerly last middle element
    check(revList5.size() == 4 && revList5.getNodeAtPos(0) != nullptr,
          "reverse after removals keeps size and valid head");


    std::cout << "\nAll tests executed.\n";

    return 0;
}