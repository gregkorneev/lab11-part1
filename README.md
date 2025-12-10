# Лабораторная работа 11 (часть 1)

Проект реализует базовые операции над графами (ориентированными и неориентированными) на C++ в учебном стиле, без сложных конструкций.
Структура проекта:

- `src/` — исходники на C++
  - `main.cpp`
  - `Graph.cpp`
  - `GraphMatrix.cpp`
- `include/` — заголовочные файлы
  - `Graph.h`
  - `GraphMatrix.h`
- `CMakeLists.txt` — файл конфигурации CMake

## Сборка и запуск

Из корня проекта выполнить один из вариантов:


1) Ручной режим с пользовательскими входными данными
```bash
rm -rf build && rm -rf data && cmake -B build && cmake --build build && ./build/lab11 && python3 .py/plot_graph_views.py && python3 .py/plot_bfs_layers.py
```
2) Автоматический режим
```bash
rm -rf build && rm -rf data && cmake -B build && cmake --build build && ./build/lab11_random && python3 .py/plot_graph_views.py && python3 .py/plot_bfs_layers.py
```
