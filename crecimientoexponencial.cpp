#include "fisica/crecimientoexponencial.h"

#include <algorithm>
#include <cmath>

#include "nucleo/excepciones.h"

CrecimientoExponencial::CrecimientoExponencial(double v0, double tasaK, double velocidadMax)
    : v0_(v0), tasaK_(tasaK), velocidadMax_(velocidadMax) {
    if (v0 <= 0.0 || tasaK < 0.0 || velocidadMax < v0)
        throw ExcepcionConfiguracion("v0 > 0, tasaK >= 0 y velocidadMax >= v0");
}

double CrecimientoExponencial::velocidadActual() const {
    const double base = std::min(v0_ * std::exp(tasaK_ * tiempo_), velocidadMax_);
    return base * escala_;
}

void CrecimientoExponencial::actualizar(double dt, Vector2D& pos, Vector2D& vel) {
    tiempo_ += dt;
    vel.x = velocidadActual();
    vel.y = 0.0;
    pos.x += vel.x * dt;
}
