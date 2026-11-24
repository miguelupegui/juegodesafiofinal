#ifndef MEMORIAAPRENDIZAJE_H
#define MEMORIAAPRENDIZAJE_H

#include <vector>

// Memoria del agente entre intentos (vive mientras el juego esté abierto).
//
// IMPORTANTE: pertenece a Juego, no al nivel ni al agente, porque el nivel se
// destruye y se vuelve a crear en cada reinicio; si la memoria viviera allí
// se perdería el historial. El agente solo guarda un puntero (no es dueño).
//
// Guarda el historial de tiempos de supervivencia y el factor de velocidad
// aprendido, que el siguiente agente lee al nacer.
class MemoriaAprendizaje {
public:
    MemoriaAprendizaje(double tiempoObjetivo, double tasaAprendizaje,
                       double factorMin, double factorMax);

    // Registra el tiempo que sobrevivió el jugador y actualiza el factor.
    void registrar(double tiempo);

    // Regla de aprendizaje (no modifica el estado):
    //   ratio = (ultimoTiempo - tiempoObjetivo) / tiempoObjetivo, acotado a [-1, 1]
    //   nuevo = factorActual * (1 + tasaAprendizaje * ratio), acotado a [factorMin, factorMax]
    // Sobrevivió mucho -> el fuego se vuelve más rápido; lo atrapó pronto -> más lento.
    // Sin historial devuelve factorActual.
    double calcularNuevoFactor(double factorActual) const;

    double factorActual() const { return factorActual_; }
    const std::vector<double>& historial() const { return historialTiempos_; }
    int intentos() const { return static_cast<int>(historialTiempos_.size()); }

private:
    std::vector<double> historialTiempos_;
    double tiempoObjetivo_;
    double tasaAprendizaje_;
    double factorMin_;
    double factorMax_;
    double factorActual_ = 1.0;
};

#endif
