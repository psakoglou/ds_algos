#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>

using namespace std;

unordered_map<int, int> memo;
unordered_map<int, int> cuts;

int rodCut(int len, unordered_map<int, int> &table)
{
    if (len == 0)
    {
        return 0;
    }
    if (memo.count(len))
    {
        return memo[len];
    }
    int mx = INT_MIN;
    int bestCut = -1;
    for (int i = 1; i <= len; i++)
    {
        int temp = table[i] + rodCut(len - i, table);
        if (temp > mx)
        {
            mx = temp;
            bestCut = i;
        }
    }
    memo[len] = mx;
    cuts[len] = bestCut;
    return mx;
}

int rodCutIter(int n, vector<int> &table)
{
    int mx = INT_MIN;
    vector<int> dp(n + 1, 0);
    for (int len = 1; len <= n; len++)
    {
        int mx = INT_MIN;
        for (int i = 1; i <= len; i++)
        {
            mx = max(mx, table[i] + dp[len - i]);
        }
        dp[len] = mx;
    }
    return dp[n];
}

int main()
{
    unordered_map<int, int> prices = {
        {1, 1},
        {2, 5},
        {3, 8},
        {4, 9},
        {5, 10},
        {6, 17},
        {7, 17},
        {8, 20},
        {9, 24},
        {10, 30},
    };

    cout << rodCut(prices.size(), prices) << endl;

    vector<int> pricesv = {0, 1, 5, 8, 9, 10, 17, 17, 20, 24, 30};

    cout << rodCutIter(pricesv.size() - 1, pricesv) << endl;

    return 0;
}