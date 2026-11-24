#ifndef CRECIMIENTOEXPONENCIAL_H
#define CRECIMIENTOEXPONENCIAL_H

#include "fisica/modelofisico.h"

// Velocidad del fuego: crece exponencialmente con el tiempo.
//   v(t) = min(v0 * e^(k*t), vMax) * escala
// - k (tasaK) controla qué tan rápido se acelera.
// - vMax evita que la velocidad crezca sin límite y el nivel sea injugable.
// - escala es un multiplicador externo: el agente lo usa para el factor
//   aprendido entre partidas y para acelerar cuando está cerca del jugador.
// Mueve en +X (el fuego avanza de atrás hacia adelante).
class CrecimientoExponencial : public ModeloFisico {
public:
    CrecimientoExponencial(double v0, double tasaK, double velocidadMax);

    double velocidadActual() const;

    void actualizar(double dt, Vector2D& pos, Vector2D& vel) override;
    void reiniciar() override { tiempo_ = 0.0; }

    void setEscala(double escala) { escala_ = escala; }
    double escala() const { return escala_; }
    double tiempo() const { return tiempo_; }

private:
    double v0_;
    double tasaK_;
    double velocidadMax_;
    double escala_ = 1.0;
    double tiempo_ = 0.0;
};

#endif
