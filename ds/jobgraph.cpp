#include <iostream>
#include <sstream>
#include <optional>
#include <string>
#include <vector>
#include <unordered_map>

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
    bool isParent;

    bool operator==(const Node &other) const
    {
        return job == other.job && runtime == other.runtime && isParent == other.isParent;
    }
};

namespace std
{
    template <>
    struct hash<Node>
    {
        std::size_t operator()(const Node &n) const noexcept
        {
            std::size_t h1 = std::hash<char>{}(n.job);
            std::size_t h2 = std::hash<unsigned int>{}(n.runtime);
            std::size_t h3 = std::hash<bool>{}(n.isParent);
            std::size_t seed = h1;
            seed ^= h2 + 0x9e3779b9 + (seed << 6) + (seed >> 2);
            seed ^= h3 + 0x9e3779b9 + (seed << 6) + (seed >> 2);
            return seed;
        }
    };
}

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

void insertToJobGraph(const LineInfo &li, unordered_map<Node, vector<Node>> &jobgraph)
{
    Node n1;
    n1.job = li.job1.value();
    n1.runtime = li.job2.has_value() ? -1 : li.runtime.value();

    Node n2;
    n2.job = li.job2.has_value() ? li.job2.value() : '_';
    n2.runtime = li.job2.has_value() ? li.runtime.value() : -1;
    if (li.job2.has_value())
    {
        n1.isParent = true;
    }

    if (jobgraph.count(n1) == 0)
    {
        jobgraph[n1] = {};
    }
    if (n2.job != '_')
    {
        jobgraph[n1].push_back(n2);
    }
}

unordered_map<Node, vector<Node>> compute(const vector<string> &lines)
{
    unordered_map<Node, vector<Node>> jobgraph;
    size_t fsize = lines.size();
    // construct
    for (unsigned int i = 0; i < fsize; i++)
    {
        LineInfo li = parse(lines[i]);
        if (!li.isValid())
        {
            cerr << "Input Error at line " << (i + 1) << endl;
            return {};
        }
        insertToJobGraph(li, jobgraph);
    }
    return jobgraph;
}

void printJobGraph(const unordered_map<Node, vector<Node>> &jobgraph)
{
    for (const auto &[node, children] : jobgraph)
    {
        cout << node.job << "(" << node.runtime << ")";
        if (!children.empty())
        {
            cout << " -> ";
            for (size_t i = 0; i < children.size(); ++i)
            {
                cout << children[i].job << "(" << children[i].runtime << ")";
                if (i + 1 < children.size())
                    cout << ", ";
            }
        }
        cout << endl;
    }
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

    auto jobgraph = compute(lines);
    cout << "Job Graph:\n";
    printJobGraph(jobgraph);

    return 0;
}