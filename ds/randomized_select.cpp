#include <iostream>
#include <vector>
#include <cstdlib> 
#include <ctime>

int partition(std::vector<int>& v, int p, int r) {
    int x = v[r];
    int i = p - 1;
    for (int j = p; j < r; j++) {
        if (v[j] <= x) {
            i++;
            std::swap(v[i], v[j]);
        }
    }
    std::swap(v[i+1], v[r]);
    return i+1;
}

int randomized_partition(std::vector<int>& v, int p, int r) {
    int range = r - p + 1;
    std::srand(std::time(nullptr));
    int i = p + (std::rand() % range);
    std::swap(v[i], v[r]);
    return partition(v, p, r);
}

int randomized_select(std::vector<int>& v, int p, int r, int k) {
    if (p == r) {
        return v[p];
    }
    int q = randomized_partition(v, p, r);
    int i = q - p + 1;
    if (k == i) {
        return v[q];
    } else if (i > k) {
        return randomized_select(v, p, q-1, k);
    } else {
        return randomized_select(v, q+1, r, k - i);
    }
}

int randomizedSelect(std::vector<int>& v, int k) {
    if (v.empty()) {
        return -1;
    }
    return randomized_select(v, 0, v.size()-1, k);
}

int main() {

    std::vector<int> v = {1, 4, 2, 6, 3, 5, 2, 4}; // 1 2 2 3 4 4 5 6

    std::cout << randomizedSelect(v, 1) << " should be " << 1 << std::endl;
    std::cout << randomizedSelect(v, 2) << " should be " << 2 << std::endl;
    std::cout << randomizedSelect(v, 3) << " should be " << 2 << std::endl;
    std::cout << randomizedSelect(v, 6) << " should be " << 4 << std::endl;
    return 0;
}