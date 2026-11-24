#include "configuraciondificultad.h"

#include "excepciones.h"

void ConfiguracionDificultad::cargarPreset(int nivel) {
    switch (nivel) {
    case 1:
        velocidadBaseFuego = 120.0;
        tasaCrecimientoFuego = 0.08;
        velocidadMaxFuego = 520.0;
        umbralCercania = 250.0;
        factorAceleracion = 1.5;
        tiempoObjetivo = 15.0;
        tasaAprendizaje = 0.10;
        factorMin = 0.6;
        factorMax = 1.6;
        densidadObstaculos = 0.5;
        velocidadPasillo = 400.0;
        break;
    case 2:
        // El nivel 2 no usa el fuego; se deja un preset base para el compañero.
        densidadObstaculos = 0.6;
        velocidadPasillo = 400.0;
        break;
    default:
        throw ExcepcionConfiguracion("el nivel " + std::to_string(nivel) + " no existe");
    }
}
