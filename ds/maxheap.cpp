#include <iostream>
#include <algorithm>
#include <vector>

class Heap {
    private:

    std::vector<int> data;

    int heapsize = 0;

    bool isMaxHeap = false;

    private:

    int _parent(int i) {
        if (i < 0) {
            return 0;
        }
        return i / 2;
    }

    int _left(int i) {
        if (i < 0) {
            return 0;
        }
        return i * 2;
    }

    int _right(int i) {
        if (i < 0) {
            return 0;
        }
        return (i * 2) + 1;
    }

    public:

    bool isMaxHeap() {
        bool ret = true;
        for (int i = heapsize; i > 0; i--) {
            ret &= data[_parent(i)] >= data[i];
        }
        return ret;
    }

    bool isMinHeap() {
        bool ret = true;
        for (int i = heapsize; i > 0; i--) {
            ret &= data[_parent(i)] <= data[i];
        }
        return ret;
    }

    void insert(int value){
        data.push_back(value);
        std::push_heap(data.begin(), data.end());
    }

    bool remove(int value){}

    void max_heapify(int i) {
        int l = _left(i);
        int r = _right(i);

        int largest = i;
        if (data[i] < data[l]) {
            largest = l;
        }
        if (data[r] > data[largest]) {
            largest = r;
        }
        if (i != largest) {
            std::swap(data[largest], data[i]);
            max_heapify(largest);
        }
    }

    void min_heapify(int i) {}

    void build_max_heap() {

    }

    void build_min_heap() {}

    void max_heap_insert() {}

    int heap_extract_max() {
        std::pop_heap(data.begin(), data.end());
        int v = data.back();
        data.pop_back();
        return v;
    }
    
    void heap_increase_key() {}

    int max() {
        return isMaxHeap ? data.front() : data.back();
    }

    int min() {
        return isMaxHeap ? data.back() : data.front();
    }

    void heapsort() {
        std::sort_heap(data.begin(), data.end());
        isMaxHeap = false;
    }

};

int main() {

    return 0;
}