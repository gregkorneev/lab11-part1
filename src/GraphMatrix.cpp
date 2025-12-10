// GraphMatrix.cpp
// Implementation of GraphMatrix declared in GraphMatrix.h

#include "../include/GraphMatrix.h"

// Construct an empty matrix graph with n vertices.  All entries are
// initialised to 0 (no edges).
GraphMatrix::GraphMatrix(int n) : n(n), adjMat(n, std::vector<int>(n, 0)) {}

// Set an edge from u to v with the given value.  A non‑zero value
// signifies the presence of an edge.  Bounds are not checked.
void GraphMatrix::setEdge(int u, int v, int value) {
    if (u < 0 || u >= n || v < 0 || v >= n) return;
    adjMat[u][v] = value;
}

// Return the number of vertices.
int GraphMatrix::size() const {
    return n;
}

// Return a constant reference to the adjacency matrix.
const std::vector<std::vector<int>>& GraphMatrix::getMatrix() const {
    return adjMat;
}

// Compute the transpose of the graph.  For each edge (u, v) in the
// original graph, the transposed graph contains (v, u).  Complexity O(V^2).
GraphMatrix GraphMatrix::getTranspose() const {
    GraphMatrix gT(n);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            gT.adjMat[j][i] = adjMat[i][j];
        }
    }
    return gT;
}

// Compute the square of the graph.  In the square graph G^2, an edge
// (i, j) exists if there is a direct edge or a two‑step path from i
// to j in the original graph.  Complexity O(V^3).
GraphMatrix GraphMatrix::squareGraph() const {
    GraphMatrix g2(n);
    // Copy existing edges to g2
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (adjMat[i][j] != 0) {
                g2.adjMat[i][j] = 1;
            }
        }
    }
    // Add edges for two‑step paths
    for (int i = 0; i < n; ++i) {
        for (int k = 0; k < n; ++k) {
            if (adjMat[i][k] != 0) {
                // There is an edge from i to k
                for (int j = 0; j < n; ++j) {
                    if (adjMat[k][j] != 0) {
                        g2.adjMat[i][j] = 1;
                    }
                }
            }
        }
    }
    return g2;
}

// Perform BFS starting at 'start'.  Returns the vertices in the order
// visited.  Uses a queue and scans each row of the adjacency matrix
// fully when exploring a vertex.  Complexity O(V^2).
std::vector<int> GraphMatrix::BFS(int start) const {
    std::vector<int> order;
    if (start < 0 || start >= n) return order;
    std::vector<bool> visited(n, false);
    std::queue<int> q;
    visited[start] = true;
    q.push(start);
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        order.push_back(u);
        // Explore all vertices v; there is an edge from u to v if
        // adjMat[u][v] is non‑zero.
        for (int v = 0; v < n; ++v) {
            if (adjMat[u][v] != 0 && !visited[v]) {
                visited[v] = true;
                q.push(v);
            }
        }
    }
    return order;
}

// Find a universal sink in the graph.  A vertex s is a universal
// sink if every other vertex has an edge to s and s has no outgoing
// edges.  Uses a linear algorithm to find a candidate and then
// verifies it.  Complexity O(V).
int GraphMatrix::findUniversalSink() const {
    int i = 0;
    int j = 0;
    // Find candidate sink: iterate through the matrix only along
    // adjMat[i][j].  If there is an edge from i to j, then i cannot
    // be a sink.  Otherwise, j cannot be a sink.
    while (i < n && j < n) {
        if (adjMat[i][j] != 0) {
            // i has an outgoing edge, so i cannot be a sink
            ++i;
        } else {
            // adjMat[i][j] == 0 => j cannot be sink (since sink must
            // have incoming edges from all other vertices).  Move to
            // next column.
            ++j;
        }
    }
    if (i >= n) {
        return -1; // no candidate found
    }
    int candidate = i;
    // Verify candidate: candidate has no outgoing edges
    for (int col = 0; col < n; ++col) {
        if (adjMat[candidate][col] != 0) {
            return -1;
        }
    }
    // Verify candidate: candidate has incoming edges from all other vertices
    for (int row = 0; row < n; ++row) {
        if (row == candidate) continue;
        if (adjMat[row][candidate] == 0) {
            return -1;
        }
    }
    return candidate;
}