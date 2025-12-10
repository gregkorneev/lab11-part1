#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
plot_bfs_layers.py
Строит пример обхода графа в ширину (BFS) от заданной стартовой вершины.
Вершины раскрашиваются по номерам слоёв (расстояние по рёбрам от старта).
Картинка сохраняется в data/png/bfs_layers.png
"""

import os
import matplotlib.pyplot as plt

try:
    import networkx as nx
except ImportError:
    raise SystemExit(
        "Модуль networkx не найден. Установи его командой:\n"
        "    pip install networkx matplotlib"
    )


def build_sample_graph():
    """
    Тот же примерный граф, что и в предыдущем скрипте,
    чтобы картинки выглядели согласованно.
    """
    G = nx.DiGraph()
    G.add_nodes_from(range(6))

    edges = [
        (0, 1),
        (0, 2),
        (1, 3),
        (2, 3),
        (3, 4),
        (4, 5),
        (1, 4),
    ]
    G.add_edges_from(edges)
    return G


def bfs_layers(G: "nx.DiGraph", start: int):
    """
    Вычисляет слои BFS от вершины start.
    Возвращает словарь: вершина -> расстояние (номер слоя).
    Недостижимые вершины получают расстояние -1.
    """
    from collections import deque

    dist = {v: -1 for v in G.nodes()}
    dist[start] = 0

    q = deque()
    q.append(start)

    while q:
        u = q.popleft()
        for v in G.successors(u):
            if dist[v] == -1:
                dist[v] = dist[u] + 1
                q.append(v)

    return dist


def main():
    os.makedirs("data/png", exist_ok=True)

    G = build_sample_graph()
    start_vertex = 0  # можно поменять при желании

    dist = bfs_layers(G, start_vertex)

    # layout фиксируем, чтобы картинка была стабильной
    pos = nx.spring_layout(G, seed=42)

    # Подготовка цветов для слоёв
    # Максимальный слой
    max_layer = max(d for d in dist.values())

    # Назначим цвет для каждого слоя
    base_colors = [
        "#1f77b4",  # слой 0
        "#ff7f0e",  # слой 1
        "#2ca02c",  # слой 2
        "#d62728",  # слой 3
        "#9467bd",  # слой 4
        "#8c564b",  # слой 5
    ]

    node_colors = []
    for v in G.nodes():
        layer = dist[v]
        if layer < 0:
            # недостижимые вершины делаем серыми
            node_colors.append("#7f7f7f")
        else:
            idx = min(layer, len(base_colors) - 1)
            node_colors.append(base_colors[idx])

    plt.figure(figsize=(6, 5))
    plt.title(f"Обход в ширину (BFS) от вершины {start_vertex}")

    nx.draw_networkx(
        G,
        pos=pos,
        with_labels=True,
        node_color=node_colors,
        node_size=700,
        arrows=True,
        font_size=10,
    )

    # Легенда по слоям
    from matplotlib.patches import Patch

    legend_handles = []
    for layer in range(0, max_layer + 1):
        idx = min(layer, len(base_colors) - 1)
        legend_handles.append(
            Patch(color=base_colors[idx], label=f"Слой {layer}")
        )

    # Проверим, есть ли недостижимые вершины
    if any(d == -1 for d in dist.values()):
        legend_handles.append(Patch(color="#7f7f7f", label="Недостижимые"))

    plt.legend(handles=legend_handles, loc="best")

    plt.axis("off")

    out_path = "data/png/bfs_layers.png"
    plt.tight_layout()
    plt.savefig(out_path, dpi=200)
    plt.close()

    print(f"Картинка сохранена в {out_path}")


if __name__ == "__main__":
    main()
