#ifndef CONFIGURACIONDIFICULTAD_H
#define CONFIGURACIONDIFICULTAD_H

enum class Dificultad { FACIL, NORMAL, DIFICIL };

class ConfiguracionDificultad {
public:
    double velocidadBaseFuego = 120.0;
    double tasaCrecimientoFuego = 0.07;
    double velocidadMaxFuego = 335.0;
    double umbralCercania = 220.0;
    double factorAceleracion = 1.25;

    double tiempoObjetivo = 22.0;
    double tasaAprendizaje = 0.08;
    double factorMin = 0.7;
    double factorMax = 1.2;

    double densidadObstaculos = 0.5;
    double velocidadPasillo = 280.0;
    double frecuenciaCarrito = 0.3;
    double amplitudCarrito = 100.0;
    double turbulencia = 3.0;

    void cargarPreset(int nivel);

    void aplicarDificultad(Dificultad d);
};

#endif
