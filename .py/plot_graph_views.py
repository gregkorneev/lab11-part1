#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
plot_graph_views.py
Создаёт картинку с тремя графами:
1) исходный ориентированный граф;
2) транспонированный граф;
3) квадрат графа (рёбра для путей длины 1–2).
Картинка сохраняется в data/png/graph_views.png
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
    Строим небольшой учебный ориентированный граф.
    Вершины: 0..5
    Рёбра: заданный список.
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


def build_graph_square(G: "nx.DiGraph") -> "nx.DiGraph":
    """
    Квадрат ориентированного графа.
    Между u и v будет ребро, если существует путь длины 1 или 2:
    u -> v (как в исходном графе) или u -> x -> v.
    """
    G2 = nx.DiGraph()
    G2.add_nodes_from(G.nodes())

    # Сохраняем исходные рёбра
    for u, v in G.edges():
        G2.add_edge(u, v)

    # Добавляем рёбра для путей длины 2
    for u in G.nodes():
        for mid in G.successors(u):
            for v in G.successors(mid):
                if u != v:
                    G2.add_edge(u, v)

    return G2


def main():
    # Гарантируем наличие папки для картинок
    os.makedirs("data/png", exist_ok=True)

    # Строим исходный граф
    G = build_sample_graph()

    # Транспонированный граф (рёбра обращены)
    GT = G.reverse(copy=True)

    # Квадрат графа
    G2 = build_graph_square(G)

    # Общий layout, чтобы расположение вершин было похожим
    pos = nx.spring_layout(G, seed=42)

    fig, axes = plt.subplots(1, 3, figsize=(15, 5))

    # 1. Исходный граф
    ax = axes[0]
    ax.set_title("Исходный граф")
    nx.draw_networkx(
        G,
        pos=pos,
        ax=ax,
        with_labels=True,
        node_size=700,
        arrows=True,
        font_size=10,
    )
    ax.axis("off")

    # 2. Транспонированный граф
    ax = axes[1]
    ax.set_title("Транспонированный граф")
    nx.draw_networkx(
        GT,
        pos=pos,
        ax=ax,
        with_labels=True,
        node_size=700,
        arrows=True,
        font_size=10,
    )
    ax.axis("off")

    # 3. Квадрат графа
    ax = axes[2]
    ax.set_title("Квадрат графа")
    nx.draw_networkx(
        G2,
        pos=pos,
        ax=ax,
        with_labels=True,
        node_size=700,
        arrows=True,
        font_size=10,
    )
    ax.axis("off")

    out_path = "data/png/graph_views.png"
    plt.tight_layout()
    plt.savefig(out_path, dpi=200)
    plt.close()

    print(f"Картинка сохранена в {out_path}")


if __name__ == "__main__":
    main()
