cmake_minimum_required(VERSION 3.15)
project(Lab5 C)

set(CMAKE_C_STANDARD 99)

# Ajouter les fichiers source
file(GLOB_RECURSE PROJECT_SOURCES CONFIGURE_DEPENDS "${CMAKE_CURRENT_LIST_DIR}/src/*.c")

# Déclarer l'exécutable pour ce sous-projet
add_executable(${PROJECT_NAME} ${PROJECT_SOURCES})

# Inclure les dossiers d'en-têtes
target_include_directories(${PROJECT_NAME} PRIVATE "${CMAKE_CURRENT_LIST_DIR}/src")

# Lier les bibliothèques
target_link_libraries(${PROJECT_NAME} PRIVATE raylib ODE::ODE)

# Définir les chemins des assets
target_compile_definitions(${PROJECT_NAME} PUBLIC ASSETS_PATH="${CMAKE_CURRENT_SOURCE_DIR}/assets/")
file(COPY ./assets/ DESTINATION ${CMAKE_BINARY_DIR}/${PROJECT_NAME}/assets/)