#include <iostream>
#include <vector>
#include <algorithm>
#include <stack>
#include <unordered_map>
#include <unordered_set>

using namespace std;

using G = unordered_map<char, vector<char>>;

void print_rec(char key, G& graph, vector<char>& currPath, vector<string>& allPaths) {
    currPath.push_back(key);

    if (graph[key].empty()) {
        string path;
        int n = currPath.size();
        for (int i = 0; i < n; i++) {
            path += currPath[i];
            if ((i + 1) < n) {
                path += " -> ";
            }
        }
        allPaths.push_back(path);
    } else {
        for (auto c : graph[key]) {
            print_rec(c, graph, currPath, allPaths);
        }
    }
    currPath.pop_back();
}

void print(G& graph) {
    vector<char> currPath;
    vector<string> allPaths;
    for (auto [k, v] : graph) {
        print_rec(k, graph, currPath, allPaths);
    }
    for (auto p : allPaths) {
        cout << p << endl;
    }
}

int main()
{
    G graph = {
        {'A', {'B', 'C', 'D'}},
        {'B', {'E', 'F'}},
        {'C', {'G', 'H'}},
        {'D', {'I'}},
        {'E', {'J'}},
        {'F', {}},
        {'G', {'J', 'K'}},
        {'H', {'K'}},
        {'I', {'L'}},
        {'J', {'M'}},
        {'K', {'M'}},
        {'L', {}},
        {'M', {}},
    };

    print(graph);

    return 0;
}