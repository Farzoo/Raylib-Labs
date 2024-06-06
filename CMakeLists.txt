cmake_minimum_required(VERSION 3.15)
project(LabProjects C)

set(CMAKE_C_STANDARD 99)

# Trouver les packages nécessaires pour tous les sous-projets
find_package(raylib CONFIG REQUIRED)
find_package(ode CONFIG REQUIRED)

# Inclure les sous-projets
add_subdirectory(./Lab1)
add_subdirectory(./Lab2)
add_subdirectory(./Lab5)
