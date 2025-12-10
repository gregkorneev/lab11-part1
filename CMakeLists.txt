cmake_minimum_required(VERSION 3.10)

project(lab11_graphs LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# 1) Основная программа с вводом от пользователя
add_executable(lab11
    src/main.cpp
    src/Graph.cpp
    src/GraphMatrix.cpp
)
target_include_directories(lab11 PRIVATE include)

# 2) Вторая программа с случайно сгенерированным графом
add_executable(lab11_random
    src/main_random.cpp
    src/Graph.cpp
    src/GraphMatrix.cpp
)
target_include_directories(lab11_random PRIVATE include)
