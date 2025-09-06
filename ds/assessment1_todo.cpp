#include <iostream>
#include <cmath>
#include <set>
#include <vector>
#include <algorithm>

class MDB {
    private:

    std::multiset<int> data;
    std::multiset<int>::iterator median;
    
    public:

    int datasize() {
        return data.size();
    }

    // O(log n + c) // insert in Red-Black Tree + O(1) to update the median
    int Add(int value) {

    }

    bool Delete(int value) {

    }

    int GetMedian() {

    }

    int GetKthLargest(int k) {

    }

    int GetKthSmallest(int k) {

    }

    // O(1)
    int ValuesInPctlBelow(double p) {

    }

    // O(1)
    int ValuesInPctlAbove(double p) {

    }

    int ValuesSmallerThan(int v) {

    }

    int ValuesLargerThan(int v) {

    }

    int CountInRange(int a, int b) {

    }

        // p in [0,100]; lower-quantile convention (floor)
    int PercentileValue(double p) const {

    }

    // floor(v): greatest <= v  (returns bool found)
    bool Floor(int v, int &out) const {

    }

    // ceil(v): smallest >= v
    bool Ceil(int v, int &out) const {

    }

    int EraseRange(int a, int b) { // inclusive

    }

    // Given stream arr and window W: O(N log W)
    std::vector<int> slidingMedian(const std::vector<int>& arr, int W) {

    }

    // average of the two middles when even
    int MedianEvenAsAvg() const {

    }

    // “how many equal to v?”
    int CountEqual(int v) const {

    }

    // (largest K values)
    std::vector<int> TopK(int k) const {

    }
};

int main() {

    MDB db;
    auto print_result = [](const std::string& test, int actual, int expected) {
        std::cout << test << " | Actual: " << actual << " | Expected: " << expected << " | " << (actual == expected ? "PASS" : "FAIL") << "\n";
    };

    // Test Add and GetMedian
    print_result("Add 5, Median", db.Add(5), 1); print_result("Median", db.GetMedian(), 5);
    print_result("Add 3, Median", db.Add(3), 2); print_result("Median", db.GetMedian(), 3);
    print_result("Add 8, Median", db.Add(8), 3); print_result("Median", db.GetMedian(), 5);
    print_result("Add 7, Median", db.Add(7), 4); print_result("Median", db.GetMedian(), 5);
    print_result("Add 2, Median", db.Add(2), 5); print_result("Median", db.GetMedian(), 5);

    // Test Delete and GetMedian
    print_result("Delete 5", db.Delete(5), true); print_result("Median", db.GetMedian(), 3);
    print_result("Delete 2", db.Delete(2), true); print_result("Median", db.GetMedian(), 7);
    print_result("Delete 8", db.Delete(8), true); print_result("Median", db.GetMedian(), 3);
    print_result("Delete 3", db.Delete(3), true); print_result("Median", db.GetMedian(), 7);
    print_result("Delete 7", db.Delete(7), true); print_result("Median", db.GetMedian(), -1);

    // Re-add for further tests
    db.Add(10); db.Add(20); db.Add(30); db.Add(40); db.Add(50);

    // Test GetKthLargest (0-based)
    print_result("Kth Largest 0", db.GetKthLargest(0), 10);
    print_result("Kth Largest 2", db.GetKthLargest(2), 30);
    print_result("Kth Largest 4", db.GetKthLargest(4), 50);
    print_result("Kth Largest 5", db.GetKthLargest(5), -1);

    // Test GetKthSmallest (0-based)
    print_result("Kth Smallest 0", db.GetKthSmallest(0), 50);
    print_result("Kth Smallest 2", db.GetKthSmallest(2), 30);
    print_result("Kth Smallest 4", db.GetKthSmallest(4), 10);
    print_result("Kth Smallest 5", db.GetKthSmallest(5), -1);

    // Test Delete non-existent value
    print_result("Delete 100", db.Delete(100), false);

    // Test GetMedian on empty
    MDB db2;
    print_result("Median empty", db2.GetMedian(), -1);

    // Test Add duplicate values
    db2.Add(1); db2.Add(1); db2.Add(1);
    print_result("Median with duplicates", db2.GetMedian(), 1);

    // Test Delete all values
    db2.Delete(1); db2.Delete(1); db2.Delete(1);
    print_result("Median after deleting all", db2.GetMedian(), -1);

    // Test GetKthLargest/Smallest on empty
    print_result("Kth Largest empty", db2.GetKthLargest(0), -1);
    print_result("Kth Smallest empty", db2.GetKthSmallest(0), -1);

    // Test ValuesInPctl (percentile queries)
    // Dataset: 10, 20, 30, 40, 50 (after previous adds)
    // Test ValuesInPctlAbove (number of values >= percentile cutoff)
    print_result("ValuesInPctlAbove 0", db.ValuesInPctlAbove(0), 5);      // All values (top 100%)
    print_result("ValuesInPctlAbove 100", db.ValuesInPctlAbove(100), 0);  // No values in top 0%
    print_result("ValuesInPctlAbove 95", db.ValuesInPctlAbove(95), 1);    // Top 5%: 1 value
    print_result("ValuesInPctlAbove 50", db.ValuesInPctlAbove(50), 3);    // Top 50%: 3 values
    print_result("ValuesInPctlAbove 20", db.ValuesInPctlAbove(20), 4);    // Top 80%: 4 values

    // Test ValuesInPctlBelow (number of values < percentile cutoff)
    print_result("ValuesInPctlBelow 0", db.ValuesInPctlBelow(0), 0);      // No values below 0th percentile
    print_result("ValuesInPctlBelow 100", db.ValuesInPctlBelow(100), 5);  // All values below 100th percentile
    print_result("ValuesInPctlBelow 95", db.ValuesInPctlBelow(95), 4);    // Bottom 95%: 4 values
    print_result("ValuesInPctlBelow 50", db.ValuesInPctlBelow(50), 2);    // Bottom 50%: 2 values
    print_result("ValuesInPctlBelow 20", db.ValuesInPctlBelow(20), 1);    // Bottom 20%: 1 value

    return 0;
}