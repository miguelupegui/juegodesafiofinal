#include "memoriaaprendizaje.h"

#include <algorithm>

#include "excepciones.h"

MemoriaAprendizaje::MemoriaAprendizaje(double tiempoObjetivo, double tasaAprendizaje,
                                       double factorMin, double factorMax)
    : tiempoObjetivo_(tiempoObjetivo), tasaAprendizaje_(tasaAprendizaje),
      factorMin_(factorMin), factorMax_(factorMax) {
    if (tiempoObjetivo <= 0.0 || tasaAprendizaje < 0.0 || factorMin <= 0.0 || factorMax < factorMin)
        throw ExcepcionConfiguracion("parametros de MemoriaAprendizaje fuera de rango");
}

double MemoriaAprendizaje::calcularNuevoFactor(double factorActual) const {
    if (historialTiempos_.empty())
        return factorActual;

    const double ultimo = historialTiempos_.back();
    const double ratio = std::clamp((ultimo - tiempoObjetivo_) / tiempoObjetivo_, -1.0, 1.0);
    const double nuevo = factorActual * (1.0 + tasaAprendizaje_ * ratio);
    return std::clamp(nuevo, factorMin_, factorMax_);
}

void MemoriaAprendizaje::registrar(double tiempo) {
    historialTiempos_.push_back(tiempo);
    factorActual_ = calcularNuevoFactor(factorActual_);
}
