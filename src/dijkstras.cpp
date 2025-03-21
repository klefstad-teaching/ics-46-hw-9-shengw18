#include "dijkstras.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <limits>
#include <stack>

using namespace std;


vector<int> dijkstra_shortest_path(const Graph& G, int source, vector<int>& previous) {
    int n = G.numVertices;
    vector<int> distances(n, INF);
    previous.assign(n, -1);
    
    using Node = pair<int, int>;
    priority_queue<Node, vector<Node>, greater<Node>> pq;

    distances[source] = 0;
    pq.push({0, source});

    while (!pq.empty()) {
        auto [dist, u] = pq.top();
        pq.pop();

        if (dist > distances[u]) continue;

        for (const Edge& edge : G[u]) {
            int v = edge.dst, weight = edge.weight;
            if (distances[u] + weight < distances[v]) {
                distances[v] = distances[u] + weight;
                previous[v] = u;
                pq.push({distances[v], v});
            }
        }
    }
    // check distance find the error
    cout << "Final distances from source " << source << ":\n";
    for (int i = 0; i < n; i++) {
        cout << "To " << i << ": " << (distances[i] == INF ? "INF" : to_string(distances[i])) << endl;
    }

    return distances;
}



vector<int> extract_shortest_path(const vector<int>& distances, const vector<int>& previous, int destination) {
    vector<int> path;
    // check
    if (distances[destination] == INF) {
        cout << "No path to " << destination << ", returning empty path." << endl;
        return path;
    }

    for (int v = destination; v != -1; v = previous[v]) {
        path.push_back(v);
    }
    reverse(path.begin(), path.end());

    cout << "Extracted path: ";
    for (int node : path) cout << node << " ";
    cout << endl;

    return path;
}


void print_path(const vector<int>& path, int total_cost) {
	if (path.empty()) {
        cout << endl;
    } else {
		for (size_t i = 0; i < path.size(); ++i) {
				cout << path[i] << ' ';
			}
		cout << endl;
	}
	cout << "Total cost is " << total_cost << endl;
}