#ifndef MOVIMIENTOOSCILATORIO_H
#define MOVIMIENTOOSCILATORIO_H

#include "modelofisico.h"

class MovimientoOscilatorio : public ModeloFisico {
public:
    MovimientoOscilatorio(double amplitud, double frecuencia, double fase = 0.0,
                          Vector2D origen = Vector2D(0.0, 0.0),
                          Vector2D eje = Vector2D(1.0, 0.0));

    double desplazamiento(double t) const;

    void actualizar(double dt, Vector2D& pos, Vector2D& vel) override;
    void reiniciar() override { tiempo = 0.0; }

    void setOrigen(const Vector2D& origen) { this->origen = origen; }
    double getTiempo() const { return tiempo; }

private:
    double amplitud;
    double frecuencia;
    double fase;
    Vector2D origen;
    Vector2D eje;
    double tiempo = 0.0;
};

#endif
