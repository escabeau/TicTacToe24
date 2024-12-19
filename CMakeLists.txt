cmake_minimum_required(VERSION 3.20)

# Nom du projet
project(TICTACTOE24)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_EXTENSIONS OFF)

# Activer FetchContent pour gérer les dépendances
include(FetchContent)

# Configuration de Raylib
set(RAYLIB_VERSION 4.5.0)
FetchContent_Declare(
    raylib
    URL https://github.com/raysan5/raylib/archive/refs/tags/${RAYLIB_VERSION}.tar.gz
)
FetchContent_MakeAvailable(raylib)

# Ajouter les fichiers source de ton projet
file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS src/*.cpp)

# Déclarer l'exécutable
add_executable(${PROJECT_NAME} ${SOURCES})

# Ajouter les fichiers d'en-tête
target_include_directories(${PROJECT_NAME} PRIVATE src)

# Ajouter l'inclusion des headers Raylib
target_include_directories(${PROJECT_NAME} PRIVATE ${raylib_SOURCE_DIR}/src)

# Lier Raylib à l'exécutable
target_link_libraries(${PROJECT_NAME} raylib)

# Ajouter des flags spécifiques à Windows
if (WIN32)
    # S'assurer que la bibliothèque est statique
    target_link_options(${PROJECT_NAME} PRIVATE -static)
    # Ajout pour éviter des erreurs liées à la console Windows
    target_link_libraries(${PROJECT_NAME} winmm gdi32)
endif()

# Supprimer les warnings liés à Raylib (optionnel)
if (MSVC)
    target_compile_options(${PROJECT_NAME} PRIVATE /W3 /WX-)
else()
    target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -Wno-unused-parameter -Wno-missing-field-initializers)
endif()

# Ajouter un message pour confirmer la configuration
message(STATUS "Raylib ${RAYLIB_VERSION} ajouté au projet et configuré.")
