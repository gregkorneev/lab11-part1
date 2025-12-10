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

## Требования

- Компилятор C++ с поддержкой стандарта C++17
- CMake (рекомендуется версии 3.10+)

## Сборка и запуск

Из корня проекта выполнить:

```bash
rm -rf build && cmake -B build && cmake --build build && ./build/lab11 && python3 .py/plot_graph_views.py && python3 .py/plot_bfs_layers.py
```
