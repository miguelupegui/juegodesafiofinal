cmake_minimum_required(VERSION 3.21)
project(JuegoChapecoense VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_library(logica STATIC
    excepciones.h
    vector2d.h
    rectangulo.h
    modelofisico.h
    movimientoparabolico.h
    movimientoparabolico.cpp
    crecimientoexponencial.h
    crecimientoexponencial.cpp
    movimientooscilatorio.h
    movimientooscilatorio.cpp
    configuraciondificultad.h
    configuraciondificultad.cpp
    memoriaaprendizaje.h
    memoriaaprendizaje.cpp
    agentefuego.h
    agentefuego.cpp
)
target_include_directories(logica PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_compile_options(logica PRIVATE -Wall -Wextra)

find_package(Qt6 REQUIRED COMPONENTS Widgets)
qt_standard_project_setup()

qt_add_executable(juego main.cpp)
target_link_libraries(juego PRIVATE logica Qt6::Widgets)