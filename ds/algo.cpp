
// Given an m x n integer matrix matrix, if an element is 0, set its entire row and column to 0's.

// m * n 

#include <vector>
#include <unordered_set>
using namespace std;

void setZeroes(vector<vector<int>>& matrix) {
    // do that for every cell that has value 0
    // loop over every cell of the matrix and if a cell is zero then 
    // row : fix i and iterate j from 0 to n-1 (j range, columns)
    // col: fix j and iterate i from 0 to m-1 (i range, rows)
    // [0] 0 0 0 
    // 0   x 
    // 0     x
    // 0       x
    // keep track of the rows and columns that you already zeroed -> dictionary for row, and columns
    // store i, j
    // check the dictionary before you loop over to zero out
    if (matrix.empty()) {
        return;
    }
    int n = matrix.size();
    int m = matrix[0].size();
    unordered_set<int> visitedCols;
    unordered_set<int> visitedRows;

    // pass 1
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (matrix[i][j] == 0) {
                visitedCols.insert(j);
                visitedRows.insert(i);
            }
        }
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (visitedCols.count(j) > 0 && visitedRows.count(i) > 0) {
                matrix[i][j] = 0;
            }
        }
    }
}