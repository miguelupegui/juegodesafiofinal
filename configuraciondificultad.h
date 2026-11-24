#ifndef CONFIGURACIONDIFICULTAD_H
#define CONFIGURACIONDIFICULTAD_H

class ConfiguracionDificultad {
public:
    // --- Fuego (agente) ---
    double velocidadBaseFuego = 120.0;
    double tasaCrecimientoFuego = 0.08;
    double velocidadMaxFuego = 520.0;
    double umbralCercania = 250.0;
    double factorAceleracion = 1.5;

    // Aprendizaje del agente
    double tiempoObjetivo = 15.0;
    double tasaAprendizaje = 0.10;
    double factorMin = 0.6;
    double factorMax = 1.6;

    // --- Nivel ---
    double densidadObstaculos = 0.5;
    double velocidadPasillo = 400.0;

    // si el nivel no existe.
    void cargarPreset(int nivel);
};

#endif
