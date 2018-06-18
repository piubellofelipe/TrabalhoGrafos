cmake_minimum_required(VERSION 3.6)
project(Grafos)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp Grafo.cpp Grafo.h No.cpp No.h Aresta.cpp Aresta.h)
add_executable(Grafos ${SOURCE_FILES} Grafo.cpp Grafo.h No.cpp No.h Aresta.cpp Aresta.h Grafo2.cpp)