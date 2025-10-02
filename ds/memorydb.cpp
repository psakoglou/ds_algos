#include <set>
#include <vector>
#include <iostream>
#include <optional>

class MemoryDB
{

    std::multiset<int> data;
    std::multiset<int>::iterator median;

public:
    int Add(int value)
    {
        if (data.empty())
        {
            data.insert(value);
            median = data.begin();
            return 1;
        }

        data.insert(value);
        std::size_t n = data.size();
        if (n % 2 == 0)
        {
            if (value < *median)
            {
                median--;
            }
            //   m
            // 2 3 3
            //   m
            // 2 3 3 4  // don't increase

            //   m
            // 2 3 3
            //   m
            // 1 2 3 3 // decrease
        }
        else
        {
            //   m
            // 1 2 3 3
            //     m
            // 1 1 2 3 3  // don't increase

            //   m
            // 1 2 3 3
            //     m
            // 1 2 3 3 4  // increase
            if (value >= *median)
            {
                median++;
            }
        }

        return data.size();
    }

    bool Delete(int value)
    {
        auto found = data.find(value);
        if (found == data.end())
        {
            return false;
        }

        std::size_t n = data.size();

        if (n % 2 == 0)
        { // even to odd
            if (median == found)
            {
                median == data.erase(found);
            }
            else if (value < *median)
            {
                median++;
                data.erase(found);
            }
            else
            {
                data.erase(found);
            }
        }
        else
        {
            if (value >= *median)
            {
                median--;
                data.erase(found);
            }
            else
            {
                data.erase(found);
            }
        }
        return true;
    }

    int GetMedian()
    {
        return data.empty() ? *median : -1;
    }

    int GetKthSmallest(int k);

    int GetPercentile(int p);

    int GetMedianAtVersion(int v);

    int GetRangeCount(int low, int high);

    bool Undo();

    std::optional<int> GetMedianOfLastN(int n);

    std::vector<int> GetTopKFrequent(int k);

    int GetApproxPercentile(double p);

    double GetAverageInRange(int low, int high);
};

int main()
{
    MemoryDB db;

    // Case 1: Add increasing numbers
    db.Add(1);
    db.Add(2);
    db.Add(3);
    std::cout << "Median of {1,2,3} = " << db.GetMedian() << " (expected 2)\n";

    // Case 2: Add duplicate numbers
    db.Add(3);
    db.Add(3);
    std::cout << "Median of {1,2,3,3,3} = " << db.GetMedian() << " (expected 3)\n";

    // Case 3: Delete a value not present
    bool deleted = db.Delete(100);
    std::cout << "Delete(100) result = " << deleted << " (expected 0)\n";

    // Case 4: Delete a value that exists
    deleted = db.Delete(2);
    std::cout << "Delete(2) result = " << deleted << " (expected 1)\n";
    std::cout << "Median after deleting 2 = " << db.GetMedian() << " (expected 3)\n";

    // Case 5: Add mix of small/large numbers
    db.Add(10);
    db.Add(20);
    db.Add(-5);
    std::cout << "Median of {-5,1,3,3,3,10,20} = "
              << db.GetMedian() << " (expected 3)\n";

    // Case 6: Delete down to empty
    db.Delete(-5);
    db.Delete(1);
    db.Delete(3);
    db.Delete(3);
    db.Delete(3);
    db.Delete(10);
    db.Delete(20);
    std::cout << "All deleted. Median should be invalid.\n";
    // You might need to adjust GetMedian to return -1 if empty.
    std::cout << "Median = " << db.GetMedian() << " (expected -1)\n";

    return 0;
}