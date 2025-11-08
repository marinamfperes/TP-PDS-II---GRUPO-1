cmake_minimum_required(VERSION 3.16)
project(GerenciadorTarefas)

set(CMAKE_CXX_STANDARD 17)

#caminho do Qt
set(CMAKE_PREFIX_PATH "C:/Qt/6.10.0/mingw_64/lib/cmake")

#encontrar o módulo de widgets do Qt
find_package(Qt6 COMPONENTS Widgets REQUIRED)

#definir os arquivos do executável
add_executable(GerenciadorTarefas
    src/main.cpp
)

#ligar o executável às bibliotecas do Qt
target_link_libraries(GerenciadorTarefas
    Qt6::Widgets
)
