#ifndef MOVIMIENTOOSCILATORIO_H
#define MOVIMIENTOOSCILATORIO_H

#include "fisica/modelofisico.h"

// Movimiento armónico simple alrededor de un punto de origen, a lo largo de un eje.
//   desplazamiento(t) = A * sen(2*pi*f*t + fase)
//   posicion = origen + eje * desplazamiento
// Usos: oscilación de la cámara (turbulencia) y vaivén del carrito vendedor.
class MovimientoOscilatorio : public ModeloFisico {
public:
    // amplitud en px, frecuencia en Hz, fase en radianes.
    // eje: dirección de oscilación (por defecto horizontal).
    MovimientoOscilatorio(double amplitud, double frecuencia, double fase = 0.0,
                          Vector2D origen = Vector2D(0.0, 0.0),
                          Vector2D eje = Vector2D(1.0, 0.0));

    double desplazamiento(double t) const;

    void actualizar(double dt, Vector2D& pos, Vector2D& vel) override;
    void reiniciar() override { tiempo_ = 0.0; }

    void setOrigen(const Vector2D& origen) { origen_ = origen; }
    double tiempo() const { return tiempo_; }

private:
    double amplitud_;
    double frecuencia_;
    double fase_;
    Vector2D origen_;
    Vector2D eje_;
    double tiempo_ = 0.0;
};

#endif
