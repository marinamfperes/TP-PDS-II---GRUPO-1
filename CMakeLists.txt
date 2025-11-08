cmake_minimum_required(VERSION 3.16)
project(GerenciadorTarefas LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Caminho para o Qt
set(CMAKE_PREFIX_PATH "C:/Qt/6.10.0/mingw_64/lib/cmake")

find_package(Qt6 REQUIRED COMPONENTS Widgets)

add_executable(GerenciadorTarefas
    src/main.cpp
)

target_link_libraries(GerenciadorTarefas PRIVATE Qt6::Widgets)
