cmake_minimum_required(VERSION 3.21)
project(JuegoChapecoense VERSION 1.0 LANGUAGES CXX)

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
    caidalibre.h
    caidalibre.cpp
    configuraciondificultad.h
    configuraciondificultad.cpp
    memoriaaprendizaje.h
    memoriaaprendizaje.cpp
    agentefuego.h
    agentefuego.cpp
    elementojuego.h
    elementojuego.cpp
    temporizadorefecto.h
    temporizadorefecto.cpp
    jugador.h
    jugador.cpp
    obstaculo.h
    maleta.h
    maleta.cpp
    carritovendedor.h
    carritovendedor.cpp
    escombro.h
    escombro.cpp
    powerup.h
    powerup.cpp
    puerta.h
    puerta.cpp
    zonasegura.h
    zonasegura.cpp
    quicktimeevent.h
    quicktimeevent.cpp
    camara.h
    camara.cpp
    nivelbase.h
    nivelbase.cpp
    nivelcabinaavion.h
    nivelcabinaavion.cpp
)
target_include_directories(logica PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_compile_options(logica PRIVATE -Wall -Wextra)

find_package(Qt6 REQUIRED COMPONENTS Widgets)
qt_standard_project_setup()

qt_add_executable(juego main.cpp)
target_link_libraries(juego PRIVATE logica Qt6::Widgets)
