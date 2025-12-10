cmake_minimum_required(VERSION 3.10)

project(graph_lab11 LANGUAGES CXX)

# Используем C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Исполняемый файл
add_executable(graph_lab11
    src/main.cpp
    src/Graph.cpp
    src/GraphMatrix.cpp
)

# Путь к заголовочным файлам
target_include_directories(graph_lab11 PRIVATE include)
