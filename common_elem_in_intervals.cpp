#include <vector>
#include <iostream>
#include <unordered_map>

using namespace std;

int maxOccurance(const vector<vector<int>> &intervals)
{
    if (intervals.empty())
    {

        return -1;
    }
    vector<pair<long long, int>> ev;
    ev.reserve(intervals.size() * 2);
    for (auto i : intervals)
    {
        int L = i[0];
        int R = i[1];
        ev.emplace_back(L, +1);
        ev.emplace_back(R + 1, -1);
    }
    sort(ev.begin(), ev.end());

    long long ans = -1;
    int curr = 0, best = 0;
    for (auto [x, d] : ev)
    {
        curr += d;
        if (curr > best)
        {
            best = curr;
            ans = x;
        }
    }
    return (int)ans;
}

int main()
{

    vector<vector<int>> intervals;
    intervals.push_back({1, 2});
    intervals.push_back({3, 5});
    intervals.push_back({4, 7});
    intervals.push_back({5, 8});
    intervals.push_back({9, 10});

    int ans = 5;

    cout << (ans == maxOccurance(intervals) ? "correct" : "incorrect") << endl;

    return 0;
}