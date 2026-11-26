#include "configuraciondificultad.h"
#include "excepciones.h"
#include <string>

using namespace std;

void ConfiguracionDificultad::cargarPreset(int nivel) {
    switch (nivel) {
    case 1:
        velocidadBaseFuego = 120.0;
        tasaCrecimientoFuego = 0.07;
        velocidadMaxFuego = 335.0;
        umbralCercania = 220.0;
        factorAceleracion = 1.25;
        tiempoObjetivo = 22.0;
        tasaAprendizaje = 0.08;
        factorMin = 0.7;
        factorMax = 1.2;
        densidadObstaculos = 0.5;
        velocidadPasillo = 280.0;
        frecuenciaCarrito = 0.3;
        amplitudCarrito = 100.0;
        turbulencia = 3.0;
        break;
    case 2:
        densidadObstaculos = 0.5;
        velocidadPasillo = 260.0;
        turbulencia = 2.0;
        break;
    default:
        throw ExcepcionConfiguracion("el nivel " + to_string(nivel) + " no existe");
    }
}

void ConfiguracionDificultad::aplicarDificultad(Dificultad d) {
    cargarPreset(1);

    if (d == Dificultad::FACIL) {
        velocidadBaseFuego = 90.0;
        tasaCrecimientoFuego = 0.05;
        velocidadMaxFuego = 270.0;
        umbralCercania = 150.0;
        factorAceleracion = 1.15;
        tiempoObjetivo = 24.0;
        tasaAprendizaje = 0.05;
        factorMax = 1.1;
        densidadObstaculos = 0.3;
        velocidadPasillo = 285.0;
        frecuenciaCarrito = 0.22;
        amplitudCarrito = 80.0;
        turbulencia = 2.0;
    } else if (d == Dificultad::DIFICIL) {
        velocidadBaseFuego = 135.0;
        tasaCrecimientoFuego = 0.08;
        velocidadMaxFuego = 350.0;
        umbralCercania = 280.0;
        factorAceleracion = 1.4;
        tiempoObjetivo = 21.0;
        tasaAprendizaje = 0.12;
        factorMin = 0.75;
        factorMax = 1.25;
        densidadObstaculos = 0.7;
        frecuenciaCarrito = 0.42;
        amplitudCarrito = 125.0;
        turbulencia = 5.0;
    }
}
