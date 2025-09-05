#include <iostream>
#include <vector>

int partition(std::vector<int>& v, int p, int r) {
    int x = v[r];
    int i =  p - 1;
    for (int j = p; j < r; j++) {
        if (v[j] <= x) {
            i++;
            std::swap(v[i], v[j]);
        }
    }
    std::swap(v[i+1], v[r]);
    return i+1;
}

void _quicksort(std::vector<int>& v, int p, int r) {
    if (p < r) {
        int q = partition(v, p, r);
        _quicksort(v, p, q-1);
        _quicksort(v, q+1, r);
    }
}

void quicksort(std::vector<int>& v) {
    _quicksort(v, 0, v.size()-1);
}

void print(std::vector<int>& v) {
    for (auto const& e : v) {
        std::cout << e << " ";
    }
    std::cout << std::endl;
}

int main() {

    std::vector<int> a = {1, 4, 7, 2, 55, 2, 1, 3, 0, 2};
    quicksort(a);
    print(a);

    std::vector<int> b = {2};
    quicksort(b);
    print(b);

    std::vector<int> c = {};
    quicksort(c);
    print(c);

    std::vector<int> d = {1, 1, 1, 1};
    quicksort(d);
    print(d);

    std::vector<int> e = {1, 2, 3, 4, 3};
    quicksort(e);
    print(e);

    return 0;
}