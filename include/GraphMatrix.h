// GraphMatrix.h
// Basic directed graph implementation using an adjacency matrix.
// Provides functions to transpose the graph, compute its square,
// perform BFS, and find a universal sink.

#ifndef GRAPHMATRIX_H
#define GRAPHMATRIX_H

#include <vector>
#include <queue>

// The GraphMatrix class represents a directed graph using an adjacency
// matrix.  The matrix adjMat[i][j] is non‑zero if there is an edge
// from i to j.  The value stored can be 1 for presence/absence; the
// algorithms in this class only test whether an entry is zero or not.
class GraphMatrix {
public:
    // Construct an empty matrix graph with n vertices.
    explicit GraphMatrix(int n);

    // Set an edge from u to v.  If value is non‑zero, the edge is
    // considered present.  No bounds checking is performed.
    void setEdge(int u, int v, int value = 1);

    // Return the number of vertices.
    int size() const;

    // Return a constant reference to the adjacency matrix.
    const std::vector<std::vector<int>>& getMatrix() const;

    // Compute and return the transpose of the graph.  All edge
    // directions are reversed.  Complexity: O(V^2).
    GraphMatrix getTranspose() const;

    // Compute and return the square of the graph.  In the square
    // graph G^2, an edge (u, w) is present if there is a path of
    // length one or two from u to w in the original graph.  Runs in
    // O(V^3) time.
    GraphMatrix squareGraph() const;

    // Perform BFS starting from the given start vertex.  Returns the
    // order in which vertices are visited.  Since this uses an
    // adjacency matrix, the complexity is O(V^2).
    std::vector<int> BFS(int start) const;

    // Find a universal sink in the graph if one exists.  A universal
    // sink is a vertex with in‑degree equal to (n‑1) and out‑degree
    // equal to 0.  Returns the index of the sink or ‑1 if no sink
    // exists.  Runs in O(V) time.
    int findUniversalSink() const;

private:
    int n;
    std::vector<std::vector<int>> adjMat;
};

#endif // GRAPHMATRIX_H