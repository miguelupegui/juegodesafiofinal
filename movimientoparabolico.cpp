#include "fisica/movimientoparabolico.h"

#include "nucleo/excepciones.h"

MovimientoParabolico::MovimientoParabolico(double gravedad, double velocidadSalto, double sueloY)
    : gravedad_(gravedad), velocidadSalto_(velocidadSalto), sueloY_(sueloY) {
    if (gravedad <= 0.0 || velocidadSalto <= 0.0)
        throw ExcepcionConfiguracion("gravedad y velocidadSalto deben ser positivas");
}

void MovimientoParabolico::iniciarSalto() {
    if (enSuelo_) {
        impulsoPendiente_ = true;
        enSuelo_ = false;
    }
}

void MovimientoParabolico::actualizar(double dt, Vector2D& pos, Vector2D& vel) {
    if (impulsoPendiente_) {
        vel.y = -velocidadSalto_;
        impulsoPendiente_ = false;
    }
    if (enSuelo_)
        return;

    pos.y += vel.y * dt + 0.5 * gravedad_ * dt * dt;
    vel.y += gravedad_ * dt;

    if (pos.y >= sueloY_) {   // aterrizó
        pos.y = sueloY_;
        vel.y = 0.0;
        enSuelo_ = true;
    }
}

void MovimientoParabolico::reiniciar() {
    enSuelo_ = true;
    impulsoPendiente_ = false;
}

double MovimientoParabolico::alturaMaxima() const {
    return (velocidadSalto_ * velocidadSalto_) / (2.0 * gravedad_);
}
