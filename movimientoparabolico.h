#ifndef MOVIMIENTOPARABOLICO_H
#define MOVIMIENTOPARABOLICO_H

#include "modelofisico.h"

// Salto del jugador: movimiento uniformemente acelerado en Y (parábola).
//   y(t+dt)  = y + vy*dt + 1/2*g*dt^2
//   vy(t+dt) = vy + g*dt
// La velocidad horizontal NO la maneja este modelo (la controla el jugador).
// Convención: y crece hacia abajo, así que la gravedad es positiva y el
// impulso del salto es una velocidad vertical negativa.
class MovimientoParabolico : public ModeloFisico {
public:
    // gravedad en px/s^2, velocidadSalto en px/s (magnitud, hacia arriba),
    // sueloY = valor de pos.y cuando el personaje está de pie.
    MovimientoParabolico(double gravedad, double velocidadSalto, double sueloY);

    // Solicita un salto. Solo tiene efecto si está en el suelo (sin doble salto).
    void iniciarSalto();

    void actualizar(double dt, Vector2D& pos, Vector2D& vel) override;
    void reiniciar() override;

    bool estaEnSuelo() const { return enSuelo_; }
    void setSueloY(double sueloY) { sueloY_ = sueloY; }
    double sueloY() const { return sueloY_; }

    // Altura máxima teórica del salto: v^2 / (2g). Útil para diseñar obstáculos.
    double alturaMaxima() const;

private:
    double gravedad_;
    double velocidadSalto_;
    double sueloY_;
    bool enSuelo_ = true;
    bool impulsoPendiente_ = false;
};

#endif
