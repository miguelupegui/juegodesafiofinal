#include "movimientooscilatorio.h"

#include <cmath>

#include "excepciones.h"

namespace {
constexpr double kDosPi = 6.283185307179586;
}

MovimientoOscilatorio::MovimientoOscilatorio(double amplitud, double frecuencia, double fase,
                                             Vector2D origen, Vector2D eje)
    : amplitud_(amplitud), frecuencia_(frecuencia), fase_(fase), origen_(origen), eje_(eje) {
    if (amplitud < 0.0 || frecuencia < 0.0)
        throw ExcepcionConfiguracion("amplitud y frecuencia no pueden ser negativas");
}

double MovimientoOscilatorio::desplazamiento(double t) const {
    return amplitud_ * std::sin(kDosPi * frecuencia_ * t + fase_);
}

void MovimientoOscilatorio::actualizar(double dt, Vector2D& pos, Vector2D& vel) {
    tiempo_ += dt;
    const double d = desplazamiento(tiempo_);
    const double v = amplitud_ * kDosPi * frecuencia_ *
                     std::cos(kDosPi * frecuencia_ * tiempo_ + fase_);
    pos = origen_.sumar(eje_.escalar(d));
    vel = eje_.escalar(v);
}
