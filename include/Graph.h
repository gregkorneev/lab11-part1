// Graph.h
// Basic directed graph implementation using adjacency lists.
// Provides functions to transpose a graph, compute its square,
// perform BFS and convert a multigraph into a simple undirected graph.

#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include <queue>
#include <unordered_set>

// The Graph class represents a directed graph using an adjacency list.
// Vertices are numbered from 0 to (numVertices - 1).  Edges are stored
// in a vector of vectors, where adj[u] contains all vertices v such that
// there is a directed edge from u to v.  This class exposes several
// utility functions for common graph algorithms.
class Graph {
public:
    // Construct an empty graph with v vertices.
    explicit Graph(int v);

    // Add a directed edge from u to v.  No bounds checking is performed.
    void addEdge(int u, int v);

    // Return the number of vertices in the graph.
    int size() const;

    // Return the adjacency list of the graph.
    const std::vector<std::vector<int>>& getAdjacencyList() const;

    // Compute and return the transpose of this graph.  All edge directions
    // are reversed.  Runs in O(V + E) time.
    Graph getTranspose() const;

    // Compute and return the square of this graph.  The square graph G^2
    // contains an edge (u, v) if there is a path in G from u to v of
    // length one or two.  Runs in O(V * (V + E)) time in the worst case.
    Graph squareGraph() const;

    // Perform a breadth‑first search starting from the given start vertex.
    // Returns the order in which vertices are visited.  Uses adjacency
    // lists and therefore runs in O(V + E) time.
    std::vector<int> BFS(int start) const;

    // Convert a multigraph (possibly containing parallel edges and loops)
    // into a simple undirected graph.  Loops are removed and multiple
    // parallel edges are collapsed into a single edge.  The result
    // contains an undirected edge (u, v) exactly once for each distinct
    // unordered pair {u, v} that appears in the original graph, with
    // u != v.  Runs in O(V + E) time.
    Graph toSimpleUndirected() const;

private:
    int numVertices;
    std::vector<std::vector<int>> adj;
};

#endif // GRAPH_H