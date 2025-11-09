cmake_minimum_required(VERSION 3.16)
project(GerenciadorTarefas LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Caminho para o Qt
set(CMAKE_PREFIX_PATH "C:/Qt/6.10.0/mingw_64/lib/cmake")

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt6 REQUIRED COMPONENTS Core Widgets)

file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS "${CMAKE_SOURCE_DIR}/src/*.cpp")
add_executable(GerenciadorTarefas ${SOURCES})

target_include_directories(GerenciadorTarefas PRIVATE "${CMAKE_SOURCE_DIR}/include")

target_link_libraries(GerenciadorTarefas PRIVATE Qt6::Core Qt6::Widgets)
