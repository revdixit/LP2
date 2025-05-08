#include <iostream>
#include <queue>
#include <stack>
#include <vector>
#include <map>
#include <set>
#include <string>
#include <unordered_map>
using namespace std;

// BFS Iterative
void bfsIterative(unordered_map<string, vector<string>> &adj, string start)
{
    queue<pair<string, int>> q;
    set<string> visited;

    q.push(make_pair(start, 0));

    cout << "BFS (Iterative):\n";
    while (!q.empty())
    {
        pair<string, int> current = q.front();
        q.pop();
        string node = current.first;
        int level = current.second;

        if (visited.find(node) == visited.end())
        {
            visited.insert(node);
            cout << "Level " << level << ": " << node << "\n";

            for (auto &neighbor : adj[node])
            {
                if (visited.find(neighbor) == visited.end())
                {
                    q.push(make_pair(neighbor, level + 1));
                }
            }
        }
    }
}

// BFS Recursive Helper
void bfsRecursiveHelper(unordered_map<string, vector<string>> &adj, queue<pair<string, int>> &q, set<string> &visited)
{
    if (q.empty())
        return;

    pair<string, int> current = q.front();
    q.pop();
    string node = current.first;
    int level = current.second;

    if (visited.find(node) == visited.end())
    {
        visited.insert(node);
        cout << "Level " << level << ": " << node << "\n";

        for (auto &neighbor : adj[node])
        {
            if (visited.find(neighbor) == visited.end())
            {
                q.push(make_pair(neighbor, level + 1));
            }
        }
    }
    bfsRecursiveHelper(adj, q, visited);
}

// BFS Recursive
void bfsRecursive(unordered_map<string, vector<string>> &adj, string start)
{
    queue<pair<string, int>> q;
    set<string> visited;

    q.push(make_pair(start, 0));

    cout << "BFS (Recursive):\n";
    bfsRecursiveHelper(adj, q, visited);
}

// DFS Iterative
void dfsIterative(unordered_map<string, vector<string>> &adj, string start)
{
    stack<pair<string, int>> s;
    set<string> visited;

    s.push(make_pair(start, 0));

    cout << "DFS (Iterative):\n";
    while (!s.empty())
    {
        pair<string, int> current = s.top();
        s.pop();
        string node = current.first;
        int level = current.second;

        if (visited.find(node) == visited.end())
        {
            visited.insert(node);
            cout << "Level " << level << ": " << node << "\n";

            for (auto it = adj[node].rbegin(); it != adj[node].rend(); ++it)
            {
                if (visited.find(*it) == visited.end())
                {
                    s.push(make_pair(*it, level + 1));
                }
            }
        }
    }
}

// DFS Recursive Helper
void dfsRecursiveHelper(unordered_map<string, vector<string>> &adj, string node, int level, set<string> &visited)
{
    visited.insert(node);
    cout << "Level " << level << ": " << node << "\n";

    for (auto &neighbor : adj[node])
    {
        if (visited.find(neighbor) == visited.end())
        {
            dfsRecursiveHelper(adj, neighbor, level + 1, visited);
        }
    }
}

// DFS Recursive
void dfsRecursive(unordered_map<string, vector<string>> &adj, string start)
{
    set<string> visited;
    cout << "DFS (Recursive):\n";
    dfsRecursiveHelper(adj, start, 0, visited);
}

// Application
void findClosestCities(unordered_map<string, vector<string>> &adj, string center)
{
    queue<pair<string, int>> q;
    set<string> visited;

    q.push(make_pair(center, 0));
    visited.insert(center);

    cout << "Cities closest to " << center << ":\n";
    while (!q.empty())
    {
        pair<string, int> current = q.front();
        q.pop();
        string city = current.first;
        int level = current.second;

        cout << city << "\n";

        for (const auto &neighbor : adj[city])
        {
            if (visited.find(neighbor) == visited.end())
            {
                visited.insert(neighbor);
                q.push(make_pair(neighbor, level + 1));
            }
        }
    }
}

void dlsHelper(unordered_map<string, vector<string>> &adj, string current, int depth, set<string> &visited, int currentDepth)
{
    if (currentDepth > depth)
    {
        return;
    }

    if (visited.find(current) == visited.end())
    {
        visited.insert(current);
        cout << current << " ";

        for (string neighbor : adj[current])
        {
            dlsHelper(adj, neighbor, depth, visited, currentDepth + 1);
        }
    }
}

// DLS
void dls(unordered_map<string, vector<string>> &adj, string start, int depth)
{
    set<string> visited;
    cout << "DLS (Depth " << depth << "):\n";
    dlsHelper(adj, start, depth, visited, 0);
}

// IDS
void ids(unordered_map<string, vector<string>> &adj, string start, int depth)
{
    cout << "IDS:\n";
    set<string> allVisited;

    while (true)
    {
        cout << "Depth " << depth << ":\n";
        set<string> visited;
        dlsHelper(adj, start, depth, visited, 0);
        allVisited.insert(visited.begin(), visited.end());

        bool allNodesVisited = true;
        for (auto &node : adj)
        {
            if (allVisited.find(node.first) == allVisited.end())
            {
                allNodesVisited = false;
                break;
            }
        }

        if (allNodesVisited)
        {
            break;
        }

        depth++;
        cout << "\n" << endl;
    }
}

// Add Edge
void addEdge(unordered_map<string, vector<string>> &adj, const string &u, const string &v)
{
    adj[u].push_back(v);
    adj[v].push_back(u);
}

// Menu
void menu(unordered_map<string, vector<string>> &adj)
{
    string startNode;
    cout << "Enter the starting node for traversal: ";
    cin >> startNode;
    int depth;

    int choice;
    do
    {
        cout << "\nMenu:\n";
        cout << "1. BFS (Iterative)\n";
        cout << "2. BFS (Recursive)\n";
        cout << "3. DFS (Iterative)\n";
        cout << "4. DFS (Recursive)\n";
        cout << "5. Application - Find the closest cities to the center city\n";
        cout << "6. DLS\n";
        cout << "7. IDS\n";
        cout << "8. Exit\n";

        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            bfsIterative(adj, startNode);
            break;
        case 2:
            bfsRecursive(adj, startNode);
            break;
        case 3:
            dfsIterative(adj, startNode);
            break;
        case 4:
            dfsRecursive(adj, startNode);
            break;
        case 5:
            findClosestCities(adj, startNode);
            break;
        case 6:
            cout << "Enter Depth: " << endl;
            cin >> depth;
            dls(adj, startNode, depth);
            break;
        case 7:
            cout << "Enter max Depth: " << endl;
            cin >> depth;
            ids(adj, startNode, depth);
            break;
        case 8:
            cout << "Exiting..." << endl;
            break;
        default:
            cout << "Invalid choice! Please try again." << endl;
        }
    } while (choice != 8);
}

int main()
{
    unordered_map<string, vector<string>> adj;
    int e;
    cout << "Enter the number of edges in the graph: ";
    cin >> e;

    cout << "Enter the edges (node1 node2):" << endl;
    for (int i = 0; i < e; i++)
    {
        string u, v;
        cin >> u >> v;
        addEdge(adj, u, v);
    }

    menu(adj);
    return 0;
}
