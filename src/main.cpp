// main.cpp
// Simple driver program to exercise the graph algorithms defined
// in Graph.h and GraphMatrix.h.  This program reads a directed graph
// from standard input, builds both an adjacency list and adjacency
// matrix representation, and then demonstrates the various
// operations: transpose, square, BFS, universal sink detection and
// conversion to a simple undirected graph.

#include <iostream>
#include "../include/Graph.h"
#include "../include/GraphMatrix.h"

// Helper function to print an adjacency list
static void printAdjList(const Graph &g) {
    const auto &adj = g.getAdjacencyList();
    for (int u = 0; u < g.size(); ++u) {
        std::cout << u << ": ";
        for (size_t i = 0; i < adj[u].size(); ++i) {
            std::cout << adj[u][i];
            if (i + 1 < adj[u].size()) std::cout << ", ";
        }
        std::cout << std::endl;
    }
}

// Helper function to print an adjacency matrix
static void printAdjMatrix(const GraphMatrix &gm) {
    const auto &mat = gm.getMatrix();
    int n = gm.size();
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            std::cout << mat[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

// Entry point
int main() {
    std::cout << "Введите количество вершин и ребер графа: ";
    int n, m;
    if (!(std::cin >> n >> m)) {
        std::cerr << "Неверный ввод." << std::endl;
        return 1;
    }
    Graph g(n);
    GraphMatrix gm(n);
    std::cout << "Введите пары вершин для направленных ребер (u v):" << std::endl;
    for (int i = 0; i < m; ++i) {
        int u, v;
        std::cin >> u >> v;
        g.addEdge(u, v);
        gm.setEdge(u, v, 1);
    }
    std::cout << "Исходный граф (списки смежности):" << std::endl;
    printAdjList(g);
    std::cout << std::endl;
    std::cout << "Исходный граф (матрица смежности):" << std::endl;
    printAdjMatrix(gm);
    std::cout << std::endl;

    // Transpose
    Graph gT = g.getTranspose();
    GraphMatrix gmT = gm.getTranspose();
    std::cout << "Транспонированный граф (списки смежности):" << std::endl;
    printAdjList(gT);
    std::cout << std::endl;
    std::cout << "Транспонированный граф (матрица смежности):" << std::endl;
    printAdjMatrix(gmT);
    std::cout << std::endl;

    // Universal sink
    int sink = gm.findUniversalSink();
    if (sink != -1) {
        std::cout << "Универсальный сток найден: вершина " << sink << std::endl;
    } else {
        std::cout << "Универсального стока нет." << std::endl;
    }
    std::cout << std::endl;

    // BFS from vertex 0 using adjacency matrix
    std::cout << "BFS обход по матрице смежности, начиная с вершины 0:" << std::endl;
    auto orderMat = gm.BFS(0);
    for (size_t i = 0; i < orderMat.size(); ++i) {
        std::cout << orderMat[i];
        if (i + 1 < orderMat.size()) std::cout << " -> ";
    }
    std::cout << std::endl << std::endl;

    // BFS from vertex 0 using adjacency list
    std::cout << "BFS обход по спискам смежности, начиная с вершины 0:" << std::endl;
    auto orderList = g.BFS(0);
    for (size_t i = 0; i < orderList.size(); ++i) {
        std::cout << orderList[i];
        if (i + 1 < orderList.size()) std::cout << " -> ";
    }
    std::cout << std::endl << std::endl;

    // Square of graph
    Graph g2 = g.squareGraph();
    GraphMatrix gm2 = gm.squareGraph();
    std::cout << "Квадрат графа (списки смежности):" << std::endl;
    printAdjList(g2);
    std::cout << std::endl;
    std::cout << "Квадрат графа (матрица смежности):" << std::endl;
    printAdjMatrix(gm2);
    std::cout << std::endl;

    // Convert multigraph to simple undirected graph
    Graph gSimple = g.toSimpleUndirected();
    std::cout << "Эквивалентный простой неориентированный граф:" << std::endl;
    printAdjList(gSimple);
    std::cout << std::endl;

    return 0;
}