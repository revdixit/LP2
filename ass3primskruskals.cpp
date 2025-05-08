
#include <bits/stdc++.h>

using namespace std;

#define INF INT_MAX

void primMST(vector<vector<int>> &graph, vector<char> &nodes, map<char, int> &nodeIndex, int V) {
    vector<int> key(V, INF);
    vector<bool> inMST(V, false);
    vector<int> parent(V, -1);
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

    key[0] = 0;
    pq.push({0, 0}); 

    while (!pq.empty()) {
        int u = pq.top().second;
        pq.pop();

        if (inMST[u]) continue;
        inMST[u] = true;

        for (int v = 0; v < V; ++v) {
            if (graph[u][v] && !inMST[v] && graph[u][v] < key[v]) {
                key[v] = graph[u][v];
                parent[v] = u;
                pq.push({key[v], v});
            }
        }
    }

    vector<tuple<char, char, int>> mstEdges;
    int totalWeight = 0;

    for (int i = 1; i < V; ++i) {
        if (parent[i] != -1) {
            char u = nodes[parent[i]];
            char v = nodes[i];
            int w = graph[i][parent[i]];
            mstEdges.push_back({u, v, w});
            totalWeight += w;
        }
    }

    sort(mstEdges.begin(), mstEdges.end());

    for (const auto &edge : mstEdges) {
        char u = std::get<0>(edge);
        char v = std::get<1>(edge);
        int w = std::get<2>(edge);
        cout << u << " - " << v << " (Weight: " << w << ")\n";
    }
    

    cout << "Total Weight: " << totalWeight << endl;
}

class DisjointSet {
    vector<int> parent, rank;
public:
    DisjointSet(int n) {
        parent.resize(n);
        rank.resize(n, 0);
        for (int i = 0; i < n; i++) parent[i] = i;
    }

    int find(int u) {
        if (parent[u] != u)
            parent[u] = find(parent[u]);
        return parent[u];
    }

    void unionSet(int u, int v) {
        int rootU = find(u), rootV = find(v);
        if (rootU != rootV) {
            if (rank[rootU] > rank[rootV])
                parent[rootV] = rootU;
            else if (rank[rootU] < rank[rootV])
                parent[rootU] = rootV;
            else {
                parent[rootV] = rootU;
                rank[rootU]++;
            }
        }
    }
};

void kruskalMST(int V, vector<tuple<int, int, int>> &edges, vector<char> &nodes) {
    sort(edges.begin(), edges.end(), [](const tuple<int, int, int> &a, const tuple<int, int, int> &b) {
        return get<2>(a) < get<2>(b);
    });

    DisjointSet ds(V);
    vector<tuple<char, char, int>> mstEdges;
    int mstWeight = 0;

    cout << "\nEdges in Kruskal's MST:\n";
    for (size_t i = 0; i < edges.size(); i++) {
        int uIndex = get<0>(edges[i]);
        int vIndex = get<1>(edges[i]);
        int w = get<2>(edges[i]);

        if (ds.find(uIndex) != ds.find(vIndex)) {
            ds.unionSet(uIndex, vIndex);
            mstEdges.push_back({nodes[uIndex], nodes[vIndex], w});
            mstWeight += w;
        }
    }

    for (const auto &edge : mstEdges) {
        char u = std::get<0>(edge);
        char v = std::get<1>(edge);
        int w = std::get<2>(edge);
        cout << u << " - " << v << " (Weight: " << w << ")\n";
    }
    

    cout << "Total Weight: " << mstWeight << endl;
}

void dijkstra(vector<vector<int>> &graph, vector<char> &nodes, int V, char source) {
    vector<int> dist(V, INF);
    vector<int> parent(V, -1);
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    map<char, int> nodeIndex;
    for (int i = 0; i < V; i++) nodeIndex[nodes[i]] = i;
    
    int src = nodeIndex[source];
    dist[src] = 0;
    pq.push({0, src});

    while (!pq.empty()) {
        int u = pq.top().second;
        pq.pop();

        for (int v = 0; v < V; ++v) {
            if (graph[u][v] && dist[u] + graph[u][v] < dist[v]) {
                dist[v] = dist[u] + graph[u][v];
                parent[v] = u;
                pq.push({dist[v], v});
            }
        }
    }

    cout << "\nDijkstra's Shortest Paths from " << source << ":\n";
    for (int i = 0; i < V; ++i) {
        cout << "Distance to " << nodes[i] << ": " << dist[i] << " | Path: ";
        vector<char> path;
        for (int v = i; v != -1; v = parent[v])
            path.push_back(nodes[v]);
        reverse(path.begin(), path.end());
        for (char c : path) cout << c << " ";
        cout << "\n";
    }
}

int main() {
    int V, E;
    cout << "Enter number of vertices and edges: ";
    cin >> V >> E;

    if (V <= 0) {
        cout << "Invalid number of vertices!" << endl;
        return 0;
    }
    if (E < 0) {
        cout << "Invalid number of edges!" << endl;
        return 0;
    }

    map<char, int> nodeIndex; 
    vector<char> nodes(V);
    vector<vector<int>> graph(V, vector<int>(V, 0));
    vector<tuple<int, int, int>> edges;

    cout << "Enter vertices (e.g., A B C): ";
    for (int i = 0; i < V; i++) {
        cin >> nodes[i];
        nodeIndex[nodes[i]] = i;  
    }

    cout << "Enter edges (u v weight), using the given vertex names:\n";
    for (int i = 0; i < E; i++) {
        char u, v;
        int w;
        cin >> u >> v >> w;

        if (nodeIndex.find(u) == nodeIndex.end() || nodeIndex.find(v) == nodeIndex.end()) {
            cout << "Invalid edge (" << u << ", " << v << ")! Skipping...\n";
            continue;
        }

        int uIndex = nodeIndex[u], vIndex = nodeIndex[v];
        graph[uIndex][vIndex] = w;
        graph[vIndex][uIndex] = w;
        edges.push_back({uIndex, vIndex, w});
    }


    primMST(graph, nodes, nodeIndex, V);
    kruskalMST(V, edges, nodes);

    char source;
    cout << "Enter source vertex for Dijkstra's: ";
    cin >> source;
    dijkstra(graph, nodes, V, source);

    return 0;
}


