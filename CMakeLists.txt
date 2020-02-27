cmake_minimum_required(VERSION 3.14)
project(DistanciasRodoviarias)

set(CMAKE_CXX_STANDARD 11)

include_directories(.)
add_executable(mapa main.cpp Mapa.cpp Mapa.h)