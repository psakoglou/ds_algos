#include <iostream>
#include <map>
#include <sstream>
#include <optional>
#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>

using namespace std;

/*
    A B 20
    B C 20
    C 30
    A D 50
    D E 30
    E 20

    output:
    100: A -> D -> E
    70: A -> B -> C
*/

struct Node
{
    char job;
    int runtime;
};

bool isValidJob(char job)
{
    return job >= 'A' && job <= 'Z';
}

bool isValidRuntime(int rt)
{
    return rt >= 0;
}

struct LineInfo
{
    optional<char> job1;
    optional<char> job2;
    optional<int> runtime;

    LineInfo(optional<char> j1, optional<char> j2, optional<int> rt) : job1(j1), job2(j2), runtime(rt) {}

    bool isValid()
    {
        return (job1.has_value() && isValidJob(job1.value())) && runtime.has_value() && (job2.has_value() ? isValidJob(job2.value()) : true);
    }
};

std::vector<std::string> tokenize(const std::string &line)
{
    std::istringstream iss(line);
    std::vector<std::string> tokens;
    std::string token;
    while (iss >> token)
    {
        tokens.push_back(token);
    }
    return tokens;
}

LineInfo parse(const std::string &line)
{
    if (line.empty() || line.size() < 3)
    {
        return LineInfo({}, {}, {});
    }
    vector<string> tokens = tokenize(line);
    int n = tokens.size();
    if (n == 3)
    {
        char j1 = tokens[0][0];
        char j2 = tokens[1][0];
        try
        {
            int rt = stoi(tokens[2]);
            return LineInfo(j1, j2, rt);
        }
        catch (const exception &e)
        {
        }
    }
    if (n == 2)
    {
        char j1 = tokens[0][0];
        try
        {
            int rt = stoi(tokens[1]);
            return LineInfo(j1, {}, rt);
        }
        catch (const exception &e)
        {
        }
    }
    return LineInfo({}, {}, {});
}

void printJobGraph(const unordered_map<char, vector<Node>> &jobgraph)
{
    for (const auto &[node, children] : jobgraph)
    {
        cout << node << ": ";
        if (!children.empty())
        {
            for (size_t i = 0; i < children.size(); ++i)
            {
                cout << "(" << children[i].job << ", " << children[i].runtime << ")";
                if (i + 1 < children.size())
                    cout << ", ";
            }
        }
        cout << endl;
    }
}

void insertToJobGraph(const LineInfo &li, unordered_map<char, vector<Node>> &jobgraph)
{

    char j1 = li.job1.value();

    if (!jobgraph.count(j1))
    {
        jobgraph[j1] = {};
    }

    Node n;
    n.job = li.job2.has_value() ? li.job2.value() : '-';
    n.runtime = li.runtime.value();
    jobgraph[j1].push_back(n);
}

void dfs(char curr, unordered_map<char, vector<Node>> &jobgraph, map<int, vector<std::string>, std::greater<int>> &ans, unordered_set<char> &visited, int currSum, string &currPath)
{
    if (visited.count(curr))
    {
        cerr << "Back Edge\n";
        return;
    }

    visited.insert(curr);

    currPath = currPath.empty() ? string(1, curr) : currPath + " -> " + string(1, curr);

    if (jobgraph[curr].empty() || (jobgraph[curr].size() == 1 && !isValidJob(jobgraph[curr][0].job)))
    {
        if (ans.count(currSum))
        {
            ans[currSum].push_back(currPath);
        }
        else
        {
            ans[currSum] = {currPath};
        }
        visited.erase(curr);
        return;
    }

    for (auto const &n : jobgraph[curr])
    {
        if (isValidJob(n.job))
        {
            dfs(n.job, jobgraph, ans, visited, currSum + n.runtime, currPath);
        }
    }
    visited.erase(curr);
}

void printAnswer(const std::map<int, vector<std::string>, std::greater<int>> &ans)
{
    cout << endl;
    for (const auto &[score, paths] : ans)
    {
        for (const auto &path : paths)
        {
            std::cout << score << ": " << path << std::endl;
        }
    }
}

void compute(const vector<string> &lines)
{
    unordered_map<char, vector<Node>> jobgraph;
    size_t fsize = lines.size();
    // construct graph
    for (unsigned int i = 0; i < fsize; i++)
    {
        LineInfo li = parse(lines[i]);
        if (!li.isValid())
        {
            cerr << "Input Error at line " << (i + 1) << endl;
        }
        insertToJobGraph(li, jobgraph);
    }
    printJobGraph(jobgraph);

    // dfs
    // i want all dfs paths and their sum
    map<int, vector<std::string>, std::greater<int>> ans;
    unordered_set<char> visited;
    int currSum = 0;
    string currPath = "";
    dfs(jobgraph.begin()->first, jobgraph, ans, visited, currSum, currPath);

    printAnswer(ans);
}

int main()
{
    // Test input simulating the example in the comment
    vector<string> lines = {
        "A B 20",
        "B C 20",
        "C 30",
        "A D 50",
        "D E 30",
        "E 20"};

    // auto jobgraph = compute(lines);
    // cout << "Job Graph:\n";
    // printJobGraph(jobgraph);
    compute(lines);

    return 0;
}