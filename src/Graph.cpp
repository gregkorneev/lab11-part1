// Graph.cpp
// Implementation of the Graph class declared in Graph.h

#include "../include/Graph.h"
#include <algorithm>

// Construct an empty graph with v vertices and no edges.
Graph::Graph(int v) : numVertices(v), adj(v) {}

// Add a directed edge from u to v.
void Graph::addEdge(int u, int v) {
    if (u < 0 || u >= numVertices || v < 0 || v >= numVertices)
        return;
    adj[u].push_back(v);
}

// Return the number of vertices.
int Graph::size() const {
    return numVertices;
}

// Return a constant reference to the adjacency list.
const std::vector<std::vector<int>>& Graph::getAdjacencyList() const {
    return adj;
}

// Compute the transpose of the graph by reversing all edges.
// For each edge (u, v) in the original graph, the transpose contains
// an edge (v, u).  Complexity: O(V + E).
Graph Graph::getTranspose() const {
    Graph gT(numVertices);
    for (int u = 0; u < numVertices; ++u) {
        for (int v : adj[u]) {
            gT.addEdge(v, u);
        }
    }
    return gT;
}

// Compute the square of the graph.  In the square graph G^2, there is
// an edge (u, w) if there is a path of length one or two from u to w
// in the original graph.  To avoid duplicate edges, we use a boolean
// array to mark which vertices have already been added for each source.
Graph Graph::squareGraph() const {
    Graph g2(numVertices);
    std::vector<bool> visited(numVertices);
    for (int u = 0; u < numVertices; ++u) {
        std::fill(visited.begin(), visited.end(), false);
        // Include all immediate neighbours of u
        for (int v : adj[u]) {
            if (v == u) continue; // skip self loops
            if (!visited[v]) {
                g2.addEdge(u, v);
                visited[v] = true;
            }
        }
        // Include all vertices reachable in two steps
        for (int v : adj[u]) {
            for (int w : adj[v]) {
                if (w == u) continue; // avoid self loops
                if (!visited[w]) {
                    g2.addEdge(u, w);
                    visited[w] = true;
                }
            }
        }
    }
    return g2;
}

// Perform a BFS on the graph starting at vertex start.  Returns a
// vector containing the vertices in the order they are discovered.
std::vector<int> Graph::BFS(int start) const {
    std::vector<int> order;
    if (start < 0 || start >= numVertices) return order;
    std::vector<bool> visited(numVertices, false);
    std::queue<int> q;
    visited[start] = true;
    q.push(start);
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        order.push_back(u);
        for (int v : adj[u]) {
            if (v < 0 || v >= numVertices) continue;
            if (!visited[v]) {
                visited[v] = true;
                q.push(v);
            }
        }
    }
    return order;
}

// Convert a multigraph (possibly with parallel edges and loops) to a
// simple undirected graph.  Loops are removed.  Multiple edges
// between the same pair of vertices are collapsed into a single edge.
Graph Graph::toSimpleUndirected() const {
    // Use a set for each vertex to avoid duplicates.
    std::vector<std::unordered_set<int>> setAdj(numVertices);
    for (int u = 0; u < numVertices; ++u) {
        for (int v : adj[u]) {
            if (v < 0 || v >= numVertices) continue;
            if (u == v) {
                // Skip loops
                continue;
            }
            // Insert both directions to make the graph undirected
            setAdj[u].insert(v);
            setAdj[v].insert(u);
        }
    }
    Graph gSimple(numVertices);
    for (int u = 0; u < numVertices; ++u) {
        for (int v : setAdj[u]) {
            gSimple.addEdge(u, v);
        }
    }
    return gSimple;
}