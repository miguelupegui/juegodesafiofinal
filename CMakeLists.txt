cmake_minimum_required(VERSION 3.16)

project(Proyecto_Final LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(Proyecto_Final main.cpp agentefuego.cpp agentefuego.h configuraciondificultad.cpp configuraciondificultad.h
                              crecimientoexponencial.cpp crecimientoexponencial.h excepciones.h memoriaaprendizaje.cpp memoriaaprendizaje.h modelofisico.h movimientooscilatorio.cpp movimientooscilatorio.h
                              movimientoparabolico.cpp movimientoparabolico.h rectangulo.h vector2d.h)

include(GNUInstallDirs)
install(TARGETS Proyecto_Final
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
