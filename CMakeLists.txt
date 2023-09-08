cmake_minimum_required(VERSION 3.14)
project(Prg2_Trees)

set(CMAKE_CXX_STANDARD 11)
include_directories(.)

add_executable(Prg2_demo main.cpp prglib.h funcoes.cpp funcoes.h)
#target_link_libraries(Prg2_demo -L${CMAKE_SOURCE_DIR}/libs prglib)
