#include "dijkstras.h"
#include <iostream>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    if (argc < 3) {
        cerr << "Usage: " << argv[0] << " <graph_file> <source_vertex>" << endl;
        return 1;
    }

    string filename = argv[1];
    int source = stoi(argv[2]);

    Graph G;
    try {
        file_to_graph(filename, G);
    } catch (const exception& e) {
        cerr << "Error: " << e.what() << endl;
        return 1;
    }

    if (source < 0 || source >= G.numVertices) {
        cerr << "Error: Source vertex out of range (0 to " << G.numVertices - 1 << ")" << endl;
        return 1;
    }

    vector<int> previous;
    vector<int> distances = dijkstra_shortest_path(G, source, previous);

    cout << "Shortest paths from vertex " << source << ":" << endl;
    for (int i = 0; i < G.numVertices; i++) {
        if (i == source) continue;
        vector<int> path = extract_shortest_path(distances, previous, i);
        cout << "To " << i << ": ";
        print_path(path, distances[i]);
    }

    return 0;
}