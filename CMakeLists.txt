cmake_minimum_required(VERSION 3.20)
project(SistemaComercioEletronico CXX)

set(CMAKE_CXX_STANDARD 17)

add_executable(SistemaComercioEletronico
    src/main.cpp
        src/vendedores.cpp
        src/vendas.cpp
)
