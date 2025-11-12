#include <iostream>
using namespace std;

struct Edge {
    int x, y, wt;
};

int bellmanFord(int v, int e, Edge edges[], int src, int* dist) {

    for (int i = 0; i < v; i++) {
        dist[i] = 1000000; 
    }
    dist[src] = 0;

    for (int i = 0; i < v; i++) {
        for (int j = 0; j < e; j++) {
            int x = edges[j].x;
            int y = edges[j].y;
            int wt = edges[j].wt;
            if (dist[x] != 1000000 && dist[x] + wt < dist[y]) {
                if (i == v - 1) {
                  
                    return 0;
                }
                dist[y] = dist[x] + wt;
            }
        }
    }
    return 1;
}

int main() {
    int v, e, src;
    cout << "Enter the number of vertices: ";
    cin >> v;

    cout << "Enter the number of edges: ";
    cin >> e;

    Edge* edges = new Edge[e];
    int* dist = new int[v];

    cout << "Enter edges in format: source destination weight\n";
    for (int i = 0; i < e; i++) {
        cin >> edges[i].x >> edges[i].y >> edges[i].wt;
    }

    cout << "Enter source vertex: ";
    cin >> src;

    if (bellmanFord(v, e, edges, src, dist)) {
        cout << "Distance from source to all vertices:\n";
        for (int i = 0; i < v; i++) {
            if (dist[i] == 1000000)
                cout << "INF\t";
            else
                cout << dist[i] << "\t";
        }
        cout << "\n";
    } else {
        cout << "Negative cycle detected.\n";
    }

    delete[] edges;
    delete[] dist;

    return 0;
}