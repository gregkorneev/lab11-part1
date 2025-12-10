// main_random.cpp
// Запуск алгоритмов на случайно сгенерированном графе
// без ввода данных пользователем.

#include <iostream>
#include <cstdlib>
#include <ctime>

#include "../include/Graph.h"
#include "../include/GraphMatrix.h"

// Печать списка смежности
static void printAdjList(const Graph &g) {
    const std::vector<std::vector<int>> &adj = g.getAdjacencyList();
    for (int u = 0; u < g.size(); ++u) {
        std::cout << u << ": ";
        for (size_t i = 0; i < adj[u].size(); ++i) {
            std::cout << adj[u][i];
            if (i + 1 < adj[u].size()) {
                std::cout << " ";
            }
        }
        std::cout << std::endl;
    }
}

// Печать матрицы смежности
static void printAdjMatrix(const GraphMatrix &gm) {
    const std::vector<std::vector<int>> &mat = gm.getMatrix();
    int n = gm.size();
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            std::cout << mat[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

// Печать расстояний BFS
static void printDistances(const std::vector<int> &dist) {
    for (size_t i = 0; i < dist.size(); ++i) {
        std::cout << "Вершина " << i << ": ";
        if (dist[i] == -1) {
            std::cout << "недостижима";
        } else {
            std::cout << "расстояние = " << dist[i];
        }
        std::cout << std::endl;
    }
}

int main() {
    std::srand(static_cast<unsigned>(std::time(nullptr)));

    // Количество вершин выбираем случайно из небольшого диапазона
    int minV = 5;
    int maxV = 8;
    int n = minV + std::rand() % (maxV - minV + 1);

    // Максимально возможное число рёбер в ориентированном графе без петель
    int maxEdges = n * (n - 1);

    // Количество рёбер: от n до примерно половины максимума
    int minE = n;
    int maxE = maxEdges / 2;
    if (maxE < minE) {
        maxE = minE;
    }
    int m = minE + std::rand() % (maxE - minE + 1);

    std::cout << "СЛУЧАЙНЫЙ ГРАФ" << std::endl;
    std::cout << "Число вершин: " << n << std::endl;
    std::cout << "Число рёбер:  " << m << std::endl;
    std::cout << std::endl;

    Graph g(n);
    GraphMatrix gm(n);

    // Заполняем граф случайными рёбрами
    int added = 0;
    while (added < m) {
        int u = std::rand() % n;
        int v = std::rand() % n;
        if (u == v) {
            continue; // без петель
        }
        g.addEdge(u, v);
        gm.setEdge(u, v, 1);
        added++;
    }

    std::cout << "Списки смежности исходного графа:" << std::endl;
    printAdjList(g);
    std::cout << std::endl;

    std::cout << "Матрица смежности исходного графа:" << std::endl;
    printAdjMatrix(gm);
    std::cout << std::endl;

    // Транспонированный граф
    Graph gT = g.getTranspose();
    GraphMatrix gmT = gm.getTranspose();

    std::cout << "Транспонированный граф (списки смежности):" << std::endl;
    printAdjList(gT);
    std::cout << std::endl;

    std::cout << "Транспонированный граф (матрица смежности):" << std::endl;
    printAdjMatrix(gmT);
    std::cout << std::endl;

    // BFS от случайной стартовой вершины
    int start = std::rand() % n;
    std::cout << "Обход в ширину (BFS) от вершины " << start << " (списки):" << std::endl;
    std::vector<int> distList = g.BFS(start);
    printDistances(distList);
    std::cout << std::endl;

    std::cout << "Обход в ширину (BFS) от вершины " << start << " (матрица):" << std::endl;
    std::vector<int> distMat = gm.BFS(start);
    printDistances(distMat);
    std::cout << std::endl;

    // Универсальный сток (по матрице)
    int sink = gm.findUniversalSink();
    if (sink == -1) {
        std::cout << "Универсальный сток в графе отсутствует." << std::endl;
    } else {
        std::cout << "Найден универсальный сток: вершина " << sink << std::endl;
    }
    std::cout << std::endl;

    // Квадрат графа
    Graph g2 = g.squareGraph();
    GraphMatrix gm2 = gm.squareGraph();

    std::cout << "Квадрат графа (списки смежности):" << std::endl;
    printAdjList(g2);
    std::cout << std::endl;

    std::cout << "Квадрат графа (матрица смежности):" << std::endl;
    printAdjMatrix(gm2);
    std::cout << std::endl;

    // Эквивалентный простой неориентированный граф
    Graph gSimple = g.toSimpleUndirected();
    std::cout << "Эквивалентный простой неориентированный граф:" << std::endl;
    printAdjList(gSimple);
    std::cout << std::endl;

    return 0;
}
